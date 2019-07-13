# -*- coding: utf-8 -*-

##
## change ReVIEW source code
##

module ReVIEW


  ## コメント「#@#」を読み飛ばす（ただし //embed では読み飛ばさない）
  LineInput.class_eval do

    def initialize(f)
      super
      @enable_comment = true
    end

    def enable_comment(flag)
      @enable_comment = flag
    end

    def gets
      line = super
      if @enable_comment
        while line && line =~ /\A\#\@\#/
          line = super
        end
      end
      return line
    end

  end


  class Compiler

    ## ブロック命令
    defblock :program, 0..3      ## プログラム
    defblock :terminal, 0..3     ## ターミナル

    ## インライン命令
    definline :secref            ## 節(Section)や項(Subsection)を参照

    private

    ## パーサを再帰呼び出しに対応させる

    def do_compile
      f = LineInput.new(StringIO.new(@chapter.content))
      @strategy.bind self, @chapter, Location.new(@chapter.basename, f)
      tagged_section_init
      parse_document(f, false)
      close_all_tagged_section
    end

    def parse_document(f, block_cmd)
      while f.next?
        case f.peek
        when /\A\#@/
          f.gets # Nothing to do
        when /\A=+[\[\s\{]/
          if block_cmd                      #+
            line = f.gets                   #+
            error "'#{line.strip}': should close '//#{block_cmd}' block before sectioning." #+
          end                               #+
          compile_headline f.gets
        #when /\A\s+\*/                     #-
        #  compile_ulist f                  #-
        when LIST_ITEM_REXP                 #+
          compile_list(f)                   #+
        when /\A\s+\d+\./
          compile_olist f
        when /\A\s*:\s/
          compile_dlist f
        when %r{\A//\}}
          return if block_cmd               #+
          f.gets
          #error 'block end seen but not opened'                   #-
          error "'//}': block-end found, but no block command opened."  #+
        #when %r{\A//[a-z]+}                       #-
        #  name, args, lines = read_command(f)     #-
        #  syntax = syntax_descriptor(name)        #-
        #  unless syntax                           #-
        #    error "unknown command: //#{name}"    #-
        #    compile_unknown_command args, lines   #-
        #    next                                  #-
        #  end                                     #-
        #  compile_command syntax, args, lines     #-
        when /\A\/\/\w+/                           #+
          parse_block_command(f)                   #+
        when %r{\A//}
          line = f.gets
          warn "`//' seen but is not valid command: #{line.strip.inspect}"
          if block_open?(line)
            warn 'skipping block...'
            read_block(f, false)
          end
        else
          if f.peek.strip.empty?
            f.gets
            next
          end
          compile_paragraph f
        end
      end
    end

    ## コードブロックのタブ展開を、LaTeXコマンドの展開より先に行うよう変更。
    ##
    ## ・たとえば '\\' を '\\textbackslash{}' に展開してからタブを空白文字に
    ##   展開しても、正しい展開にはならないことは明らか。先にタブを空白文字に
    ##   置き換えてから、'\\' を '\\textbackslash{}' に展開すべき。
    ## ・またタブ文字の展開は、本来はBuilderではなくCompilerで行うべきだが、
    ##   Re:VIEWの設計がまずいのでそうなっていない。
    ## ・'//table' と '//embed' ではタブ文字の展開は行わない。
    def read_block_for(cmdname, f)   # 追加
      disable_comment = cmdname == :embed    # '//embed' では行コメントを読み飛ばさない
      ignore_inline   = cmdname == :embed    # '//embed' ではインライン命令を解釈しない
      enable_detab    = cmdname !~ /\A(?:em)?table\z/  # '//table' ではタブ展開しない
      f.enable_comment(false) if disable_comment
      lines = read_block(f, ignore_inline, enable_detab)
      f.enable_comment(true)  if disable_comment
      return lines
    end
    def read_block(f, ignore_inline, enable_detab=true)   # 上書き
      head = f.lineno
      buf = []
      builder = @strategy                            #+
      f.until_match(%r{\A//\}}) do |line|
        if ignore_inline
          buf.push line
        elsif line !~ /\A\#@/
          #buf.push text(line.rstrip)                #-
          line = line.rstrip                         #+
          line = builder.detab(line) if enable_detab #+
          buf << text(line)                          #+
        end
      end
      unless %r{\A//\}} =~ f.peek
        error "unexpected EOF (block begins at: #{head})"
        return buf
      end
      f.gets # discard terminator
      buf
    end

    ## ブロック命令を入れ子可能に変更（'//note' と '//quote'）

    def parse_block_command(f)
      line = f.gets()
      lineno = f.lineno
      line =~ /\A\/\/(\w+)(\[.*\])?(\{)?$/  or
        error "'#{line.strip}': invalid block command format."
      cmdname = $1.intern; argstr = $2; curly = $3
      ##
      prev = @strategy.doc_status[cmdname]
      @strategy.doc_status[cmdname] = true
      ## 引数を取り出す
      syntax = syntax_descriptor(cmdname)  or
        error "'//#{cmdname}': unknown command"
      args = parse_args(argstr || "", cmdname)
      begin
        syntax.check_args args
      rescue CompileError => err
        error err.message
      end
      ## ブロックをとらないコマンドにブロックが指定されていたらエラー
      if curly && !syntax.block_allowed?
        error "'//#{cmdname}': this command should not take block (but given)."
      end
      ## ブロックの入れ子をサポートしてあれば、再帰的にパースする
      handler = "on_#{cmdname}_block"
      builder = @strategy
      if builder.respond_to?(handler)
        if curly
          builder.__send__(handler, *args) do
            parse_document(f, cmdname)
          end
          s = f.peek()
          f.peek() =~ /\A\/\/}/  or
            error "'//#{cmdname}': not closed (reached to EOF)"
          f.gets()   ## '//}' を読み捨てる
        else
          builder.__send__(handler, *args)
        end
      ## そうでなければ、従来と同じようにパースする
      elsif builder.respond_to?(cmdname)
        if !syntax.block_allowed?
          builder.__send__(cmdname, *args)
        elsif curly
          lines = read_block_for(cmdname, f)
          builder.__send__(cmdname, lines, *args)
        else
          lines = default_block(syntax)
          builder.__send__(cmdname, lines, *args)
        end
      else
        error "'//#{cmdname}': #{builder.class.name} not support this command"
      end
      ##
      @strategy.doc_status[cmdname] = prev
    end

    ## 箇条書きの文法を拡張

    alias parse_text text

    LIST_ITEM_REXP = /\A( +)(\*+|\-+) +/    # '*' は unordred list、'-' は ordered list

    def compile_list(f)
      line = f.gets()
      line =~ LIST_ITEM_REXP
      indent = $1
      char = $2[0]
      $2.length == 1  or
        error "#{$2[0]=='*'?'un':''}ordered list should start with level 1"
      line = parse_list(f, line, indent, char, 1)
      f.ungets(line)
    end

    def parse_list(f, line, indent, char, level)
      if char != '*' && line =~ LIST_ITEM_REXP
        start_num, _ = $'.lstrip().split(/\s+/, 2)
      end
      st = @strategy
      char == '*' ? st.ul_begin { level } : st.ol_begin(start_num) { level }
      while line =~ LIST_ITEM_REXP  # /\A( +)(\*+|\-+) +/
        $1 == indent  or
          error "mismatched indentation of #{$2[0]=='*'?'un':''}ordered list"
        mark = $2
        text = $'
        if mark.length == level
          break unless mark[0] == char
          line = parse_item(f, text.lstrip(), indent, char, level)
        elsif mark.length < level
          break
        else
          raise "internal error"
        end
      end
      char == '*' ? st.ul_end { level } : st.ol_end { level }
      return line
    end

    def parse_item(f, text, indent, char, level)
      if char != '*'
        num, text = text.split(/\s+/, 2)
        text ||= ''
      end
      #
      buf = [parse_text(text)]
      while (line = f.gets()) && line =~ /\A( +)/ && $1.length > indent.length
        buf << parse_text(line)
      end
      #
      st = @strategy
      char == '*' ? st.ul_item_begin(buf) : st.ol_item_begin(buf, num)
      rexp = LIST_ITEM_REXP  # /\A( +)(\*+|\-+) +/
      while line =~ rexp && $2.length > level
        $2.length == level + 1  or
          error "invalid indentation level of (un)ordred list"
        line = parse_list(f, line, indent, $2[0], $2.length)
      end
      char == '*' ? st.ul_item_end() : st.ol_item_end()
      #
      return line
    end

  end


  Book::ListIndex.class_eval do

    ## '//program' と '//terminal' をサポートするよう拡張
    def self.item_type  # override
      #'(list|listnum)'            # original
      '(list|listnum|program|terminal)'
    end

    ## '//list' や '//terminal' のラベル（第1引数）を省略できるよう拡張
    def self.parse(src, *args)  # override
      items = []
      seq = 1
      src.grep(%r{\A//#{item_type}}) do |line|
        if id = line.slice(/\[(.*?)\]/, 1)
          next if id.empty?                     # 追加
          items.push item_class.new(id, seq)
          seq += 1
          ReVIEW.logger.warn "warning: no ID of #{item_type} in #{line}" if id.empty?
        end
      end
      new(items, *args)
    end

  end


  Book::Compilable.module_eval do

    def content   # override
      ## //list[?] や //terminal[?] の '?' をランダム文字列に置き換える。
      ## こうすると、重複しないラベルをいちいち指定しなくても、ソースコードや
      ## ターミナルにリスト番号がつく。ただし @<list>{} での参照はできない。
      unless @_done
        pat = Book::ListIndex.item_type  # == '(list|listnum|program|terminal)'
        @content = @content.gsub(/^\/\/#{pat}\[\?\]/) { "//#{$1}[#{_random_label()}]" }
        ## (experimental) 範囲コメント（'#@+++' '#@---'）を行コメント（'#@#'）に変換
        @content = @content.gsub(/^\#\@\+\+\+$.*?^\#\@\-\-\-$/m) { $&.gsub(/^/, '#@#') }
        @_done = true
      end
      @content
    end

    module_function

    def _random_label
      "_" + rand().to_s[2..10]
    end

  end


  Catalog.class_eval do

    def parts_with_chaps
      ## catalog.ymlの「CHAPS:」がnullのときエラーになるのを防ぐ
      (@yaml['CHAPS'] || []).flatten.compact
    end

  end


  class Builder

    ## ul_item_begin() だけあって ol_item_begin() がないのはどうかと思う。
    ## ol の入れ子がないからといって、こういう非対称な設計はやめてほしい。
    def ol_item_begin(lines, _num)
      ol_item(lines, _num)
    end
    def ol_item_end()
    end

    protected

    def truncate_if_endwith?(str)
      sio = @output   # StringIO object
      if sio.string.end_with?(str)
        pos = sio.pos - str.length
        sio.seek(pos)
        sio.truncate(pos)
        true
      else
        false
      end
    end

    def enter_context(key)
      @doc_status[key] = true
    end

    def exit_context(key)
      @doc_status[key] = nil
    end

    def with_context(key)
      enter_context(key)
      return yield
    ensure
      exit_context(key)
    end

    def within_context?(key)
      return @doc_status[key]
    end

    def within_codeblock?
      d = @doc_status
      d[:program] || d[:terminal] \
      || d[:list] || d[:emlist] || d[:listnum] || d[:emlistnum] \
      || d[:cmd] || d[:source]
    end

    ## 入れ子可能なブロック命令

    public

    def on_note_block      caption=nil, &b; on_minicolumn :note     , caption, &b; end
    def on_memo_block      caption=nil, &b; on_minicolumn :memo     , caption, &b; end
    def on_tip_block       caption=nil, &b; on_minicolumn :tip      , caption, &b; end
    def on_info_block      caption=nil, &b; on_minicolumn :info     , caption, &b; end
    def on_warning_block   caption=nil, &b; on_minicolumn :warning  , caption, &b; end
    def on_important_block caption=nil, &b; on_minicolumn :important, caption, &b; end
    def on_caution_block   caption=nil, &b; on_minicolumn :caution  , caption, &b; end
    def on_notice_block    caption=nil, &b; on_minicolumn :notice   , caption, &b; end

    protected

    def on_minicolumn(type, caption=nil, &b)
      raise NotImplementedError.new("#{self.class.name}#on_minicolumn(): not implemented yet.")
    end

    public

    ## コードブロック（//program, //terminal）

    CODEBLOCK_OPTIONS = {
      'fold'   => true,
      'lineno' => false,
      'linenowidth' => -1,
      'eolmark'     => false,
      'foldmark'    => true,
      'lang'        => nil,
    }

    ## プログラム用ブロック命令
    ## ・//list と似ているが、長い行を自動的に折り返す
    ## ・seqsplit.styの「\seqsplit{...}」コマンドを使っている
    def program(lines, id=nil, caption=nil, optionstr=nil)
      _codeblock('program', lines, id, caption, optionstr)
    end

    ## ターミナル用ブロック命令
    ## ・//cmd と似ているが、長い行を自動的に折り返す
    ## ・seqsplit.styの「\seqsplit{...}」コマンドを使っている
    def terminal(lines, id=nil, caption=nil, optionstr=nil)
      _codeblock('terminal', lines, id, caption, optionstr)
    end

    protected

    def _codeblock(blockname, lines, id, caption, optionstr)
      raise NotImplementedError.new("#{self.class.name}#_codeblock(): not implemented yet.")
    end

    def _each_block_option(option_str)
      option_str.split(',').each do |kvs|
        k, v = kvs.split('=', 2)
        yield k, v
      end if option_str && !option_str.empty?
    end

    def _parse_codeblock_optionstr(optionstr, blockname)  # parse 'fold={on|off},...'
      opts = {}
      return opts if optionstr.nil? || optionstr.empty?
      vals = {nil=>true, 'on'=>true, 'off'=>false}
      optionstr.split(',').each_with_index do |x, i|
        x = x.strip()
        x =~ /\A([-\w]+)(?:=(.*))?\z/  or
          raise "//#{blockname}[][][#{x}]: invalid option format."
        k, v = $1, $2
        case k
        when 'fold', 'eolmark', 'foldmark'
          if vals.key?(v)
            opts[k] = vals[v]
          else
            raise "//#{blockname}[][][#{x}]: expected 'on' or 'off'."
          end
        when 'lineno'
          if vals.key?(v)
            opts[k] = vals[v]
          elsif v =~ /\A\d+\z/
            opts[k] = v.to_i
          elsif v =~ /\A\d+-?\d*(?:\&+\d+-?\d*)*\z/
            opts[k] = v
          else
            raise "//#{blockname}[][][#{x}]: expected line number pattern."
          end
        when 'linenowidth'
          if v =~ /\A-?\d+\z/
            opts[k] = v.to_i
          else
            raise "//#{blockname}[][][#{x}]: expected integer value."
          end
        when 'lang'
          if v
            opts[k] = v
          else
            raise "//#{blockname}[][][#{x}]: requires option value."
          end
        else
          if i == 0
            opts['lang'] = v
          else
            raise "//#{blockname}[][][#{x}]: unknown option."
          end
        end
      end
      return opts
    end

    def _build_caption_str(id, caption)
      str = ""
      with_context(:caption) do
        str = compile_inline(caption) if caption.present?
      end
      if id.present?
        number = _build_caption_number(id)
        prefix = "#{I18n.t('list')}#{number}#{I18n.t('caption_prefix')}"
        str = "#{prefix}#{str}"
      end
      return str
    end

    def _build_caption_number(id)
      chapter = get_chap()
      number = @chapter.list(id).number
      return chapter.nil? \
           ? I18n.t('format_number_header_without_chapter', [number]) \
           : I18n.t('format_number_header', [chapter, number])
    rescue KeyError
      error "no such list: #{id}"
    end

    public

    ## 節 (Section) や項 (Subsection) を参照する。
    ## 引数 id が節や項のラベルでないなら、エラー。
    ## 使い方： @<subsec>{label}
    def inline_secref(id)  # 参考：ReVIEW::Builder#inline_hd(id)
      ## 本来、こういった処理はParserで行うべきであり、Builderで行うのはおかしい。
      ## しかしRe:VIEWのアーキテクチャがよくないせいで、こうせざるを得ない。無念。
      sec_id = id
      chapter = nil
      if id =~ /\A([^|]+)\|(.+)/
        chap_id = $1; sec_id = $2
        chapter = @book.contents.detect {|chap| chap.id == chap_id }  or
          error "@<secref>{#{id}}: chapter '#{chap_id}' not found."
      end
      begin
        _inline_secref(chapter || @chapter, sec_id)
      rescue KeyError
        error "@<secref>{#{id}}: section (or subsection) not found."
      end
    end

    private

    def _inline_secref(chap, id)
      sec_id = chap.headline(id).id
      num, title = _get_secinfo(chap, sec_id)
      level = num.split('.').length
      #
      secnolevel = @book.config['secnolevel']
      if secnolevel + 1 < level
        error "'secnolevel: #{secnolevel}' should be >= #{level-1} in config.yml"
      ## config.ymlの「secnolevel:」が3以上なら、項 (Subsection) にも
      ## 番号がつく。なので、節 (Section) のタイトルは必要ない。
      elsif secnolevel + 1 > level
        parent_title = nil
      ## そうではない場合は、節 (Section) と項 (Subsection) とを組み合わせる。
      ## たとえば、"「1.1 イントロダクション」内の「はじめに」" のように。
      elsif secnolevel + 1 == level
        parent_id = sec_id.sub(/\|[^|]+\z/, '')
        _, parent_title = _get_secinfo(chap, parent_id)
      else
        raise "not reachable"
      end
      #
      return _build_secref(chap, num, title, parent_title)
    end

    def _get_secinfo(chap, id)  # 参考：ReVIEW::LATEXBuilder#inline_hd_chap()
      num = chap.headline_index.number(id)
      caption = compile_inline(chap.headline(id).caption)
      if chap.number && @book.config['secnolevel'] >= num.split('.').size
        caption = "#{chap.headline_index.number(id)} #{caption}"
      end
      title = I18n.t('chapter_quote', caption)
      return num, title
    end

    def _build_secref(chap, num, title, parent_title)
      raise NotImplementedError.new("#{self.class.name}#_build_secref(): not implemented yet.")
    end

  end


  class LATEXBuilder

    ## 改行命令「\\」のあとに改行文字「\n」を置かない。
    ##
    ## 「\n」が置かれると、たとえば
    ##
    ##     foo@<br>{}
    ##     bar
    ##
    ## が
    ##
    ##     foo\\
    ##
    ##     bar
    ##
    ## に展開されてしまう。
    ## つまり改行のつもりが改段落になってしまう。
    def inline_br(_str)
      #"\\\\\n"   # original
      "\\\\{}"
    end


    ## コードブロック（//program, //terminal）

    def program(lines, id=nil, caption=nil, optionstr=nil)
      _codeblock('program', lines, id, caption, optionstr)
    end

    def terminal(lines, id=nil, caption=nil, optionstr=nil)
      _codeblock('terminal', lines, id, caption, optionstr)
    end

    protected

    ## コードブロック（//program, //terminal）
    def _codeblock(blockname, lines, id, caption, optionstr)
      ## ブロックコマンドのオプション引数はCompilerクラスでパースすべき。
      ## しかしCompilerクラスがそのような設計になってないので、
      ## 仕方ないのでBuilderクラスでパースする。
      opts = _parse_codeblock_optionstr(optionstr, blockname)
      CODEBLOCK_OPTIONS.each {|k, v| opts[k] = v unless opts.key?(k) }
      #
      if opts['eolmark']
        lines = lines.map {|line| "#{detab(line)}\\startereolmark{}" }
      else
        lines = lines.map {|line| detab(line) }
      end
      #
      if id.present? || caption.present?
        str = _build_caption_str(id, caption)
        puts "\\startercodeblockcaption{#{str}}"
        puts "\\label{#{id}}" if id
      end
      #
      if within_context?(:note)
        yes = truncate_if_endwith?("\\begin{starternoteinner}\n")
        puts "\\end{starternoteinner}" unless yes
      end
      #
      environ = "starter#{blockname}"
      print "\\begin{#{environ}}"
      print "\\startersetfoldmark{}" unless opts['foldmark']
      if opts['eolmark']
        print "\\startereolmarkdark{}"  if blockname == 'terminal'
        print "\\startereolmarklight{}" if blockname != 'terminal'
      end
      if opts['lineno']
        gen = LineNumberGenerator.new(opts['lineno'])
        width = opts['linenowidth']
        if width && width >= 0
          if width == 0
            last_lineno = gen.each.take(lines.length).compact.last
            width = last_lineno.to_s.length
          end
          print "\\startersetfoldindentwidth{#{'9'*(width+2)}}"
          format = "\\textcolor{gray}{%#{width}s:} "
        else
          format = "\\starterlineno{%s}"
        end
        buf = []
        opt_fold = opts['fold']
        lines.zip(gen).each do |x, n|
          buf << ( opt_fold \
                   ? "#{format % n.to_s}\\seqsplit{#{x}}" \
                   : "#{format % n.to_s}#{x}" )
        end
        print buf.join("\n")
      else
        print "\\seqsplit{"       if opts['fold']
        print lines.join("\n")
        print "}"                 if opts['fold']
      end
      puts "\\end{#{environ}}"
      puts "\\begin{starternoteinner}" if within_context?(:note)
      nil
    end

    public

    ## ・\caption{} のかわりに \reviewimagecaption{} を使うよう修正
    ## ・「scale=X」に加えて「pos=X」も受け付けるように拡張
    def image_image(id, caption, option_str)
      pos = nil; border = nil; arr = []
      _each_block_option(option_str) do |k, v|
        case k
        when 'pos'
          v =~ /\A[Hhtb]+\z/  or  # H: Here, h: here, t: top, b: bottom
            raise "//image[][][pos=#{v}]: expected 'pos=H' or 'pos=h'."
          pos = v     # detect 'pos=H' or 'pos=h'
        when 'border'
          case v
          when nil  ; border = true
          when 'on' ; border = true
          when 'off'; border = false
          else
            raise "//image[][][border=#{v}]: expected 'border=on' or 'border=off'"
          end
        else
          arr << (v.nil? ? k : "#{k}=#{v}")
        end
      end
      #
      metrics = parse_metric('latex', arr.join(","))
      puts "\\begin{reviewimage}[#{pos}]%%#{id}" if pos
      puts "\\begin{reviewimage}%%#{id}"     unless pos
      metrics = "width=\\maxwidth" unless metrics.present?
      puts "\\starterimageframe{%" if border
      puts "\\includegraphics[#{metrics}]{#{@chapter.image(id).path}}%"
      puts "}%"                    if border
      with_context(:caption) do
        #puts macro('caption', compile_inline(caption)) if caption.present?  # original
        puts macro('reviewimagecaption', compile_inline(caption)) if caption.present?
      end
      puts macro('label', image_label(id))
      puts "\\end{reviewimage}"
    end

    def _build_secref(chap, num, title, parent_title)
      s = ""
      ## 親セクションのタイトルがあれば使う
      if parent_title
        s << "%s内の" % parent_title   # TODO: I18n化
      end
      ## 対象セクションへのリンクを作成する
      if @book.config['chapterlink']
        label = "sec:" + num.gsub('.', '-')
        s << "\\reviewsecref{#{title}}{#{label}}"
      else
        s << title
      end
      return s
    end

    ###

    public

    def ul_begin
      blank
      puts '\begin{starteritemize}'    # instead of 'itemize'
    end

    def ul_end
      puts '\end{starteritemize}'      # instead of 'itemize'
      blank
    end

    def ol_begin(start_num=nil)
      blank
      puts '\begin{starterenumerate}'  # instead of 'enumerate'
      if start_num.nil?
        return true unless @ol_num
        puts "\\setcounter{enumi}{#{@ol_num - 1}}"
        @ol_num = nil
      end
    end

    def ol_end
      puts '\end{starterenumerate}'    # instead of 'enumerate'
      blank
    end

    def ol_item_begin(lines, num)
      str = lines.join
      num = escape(num).sub(']', '\rbrack{}')
      puts "\\item[#{num}] #{str}"
    end

    def ol_item_end()
    end

    protected

    ## 入れ子可能なブロック命令

    def on_minicolumn(type, caption, &b)
      puts "\\begin{reviewminicolumn}\n"
      if caption.present?
        @doc_status[:caption] = true
        puts "\\reviewminicolumntitle{#{compile_inline(caption)}}\n"
        @doc_status[:caption] = nil
      end
      yield
      puts "\\end{reviewminicolumn}\n"
    end

  end


  class HTMLBuilder

    ## コードブロック（//program, //terminal）

    def program(lines, id=nil, caption=nil, optionstr=nil)
      _codeblock('program', 'code', lines, id, caption, optionstr)
    end

    def terminal(lines, id=nil, caption=nil, optionstr=nil)
      _codeblock('terminal', 'cmd-code', lines, id, caption, optionstr)
    end

    protected

    def _codeblock(blockname, classname, lines, id, caption, optionstr)
      ## ブロックコマンドのオプション引数はCompilerクラスでパースすべき。
      ## しかしCompilerクラスがそのような設計になってないので、
      ## 仕方ないのでBuilderクラスでパースする。
      opts = _parse_codeblock_optionstr(optionstr, blockname)
      CODEBLOCK_OPTIONS.each {|k, v| opts[k] = v unless opts.key?(k) }
      #
      if opts['eolmark']
        lines = lines.map {|line| "#{detab(line)}<small class=\"startereolmark\"></small>" }
      else
        lines = lines.map {|line| detab(line) }
      end
      #
      puts "<div id=\"#{normalize_id(id)}\" class=\"#{classname}\">" if id.present?
      puts "<div class=\"#{classname}\">"                        unless id.present?
      #
      if id.present? || caption.present?
        str = _build_caption_str(id, caption)
        print "<p class=\"caption\">#{str}</p>\n"
        classattr = "list"
      else
        classattr = "emlist"
      end
      #
      lang = opts['lang']
      lang = File.extname(id || "").gsub(".", "") if lang.blank?
      classattr << " language-#{lang}" unless lang.blank?
      classattr << " highlight"        if highlight?
      print "<pre class=\"#{classattr}\">"
      #
      gen = opts['lineno'] ? LineNumberGenerator.new(opts['lineno']).each : nil
      buf = []
      lines.each_with_index do |line, i|
        buf << "#{gen.next}".rjust(2) << ": " if gen
        buf << line << "\n"
      end
      puts highlight(body: buf.join(), lexer: lang,
                     format: "html", linenum: !!gen,
                     #options: {linenostart: start}
                     )
      #
      print "</pre>\n"
      print "</div>\n"
    end

    public

    ## コードリスト（//list, //emlist, //listnum, //emlistnum, //cmd, //source）
    def list(lines, id=nil, caption=nil, lang=nil)
      _codeblock("list", "caption-code", lines, id, caption, _codeblock_optstr(lang, false))
    end
    def listnum(lines, id=nil, caption=nil, lang=nil)
      _codeblock("listnum", "code", lines, id, caption, _codeblock_optstr(lang, true))
    end
    def emlist(lines, caption=nil, lang=nil)
      _codeblock("emlist", "emlist-code", lines, nil, caption, _codeblock_optstr(lang, false))
    end
    def emlistnum(lines, caption=nil, lang=nil)
      _codeblock("emlistnum", "emlistnum-code", lines, nil, caption, _codeblock_optstr(lang, true))
    end
    def source(lines, caption=nil, lang=nil)
      _codeblock("source", "source-code", lines, nil, caption, _codeblock_optstr(lang, false))
    end
    def cmd(lines, caption=nil, lang=nil)
      lang ||= "shell-session"
      _codeblock("cmd", "cmd-code", lines, nil, caption, _codeblock_optstr(lang, false))
    end
    def _codeblock_optstr(lang, lineno_flag)
      arr = []
      arr << lang if lang
      if lineno_flag
        first_line_num = line_num()
        arr << "lineno=#{first_line_num}"
        arr << "linenowidth=0"
      end
      return arr.join(",")
    end
    private :_codeblock_optstr

    protected

    ## @<secref>{}

    def _build_secref(chap, num, title, parent_title)
      s = ""
      ## 親セクションのタイトルがあれば使う
      if parent_title
        s << "%s内の" % parent_title   # TODO: I18n化
      end
      ## 対象セクションへのリンクを作成する
      if @book.config['chapterlink']
        filename = "#{chap.id}#{extname()}"
        dom_id = 'h' + num.gsub('.', '-')
        s << "<a href=\"#{filename}##{dom_id}\">#{title}</a>"
      else
        s << title
      end
      return s
    end

    public

    ## 順序つきリスト

    def ol_begin(start_num=nil)
      @_ol_types ||= []    # stack
      case start_num
      when nil
        type = "1"; start = 1
      when /\A(\d+)\.\z/
        type = "1"; start = $1.to_i
      when /\A([A-Z])\.\z/
        type = "A"; start = $1.ord - 'A'.ord + 1
      when /\A([a-z])\.\z/
        type = "a"; start = $1.ord - 'a'.ord + 1
      else
        type = nil; start = nil
      end
      if type
        puts "<ol start=\"#{start}\" type=\"#{type}\">"
      else
        puts "<ul>"
      end
      @_ol_types.push(type)
    end

    def ol_end()
      ol = !! @_ol_types.pop()
      if ol
        puts "</ol>"
      else
        puts "</ul>"
      end
    end

    def ol_item_begin(lines, num)
      ol = !! @_ol_types[-1]
      if ol
        print "<li>#{lines.join}"
      else
        print "<li>#{escape_html(num)} #{lines.join}"
      end
    end

    def ol_item_end()
      puts "</li>"
    end

    protected

    ## 入れ子可能なブロック命令

    def on_minicolumn(type, caption, &b)
      puts "<div class=\"#{type}\">"
      puts "<p class=\"caption\">#{compile_inline(caption)}</p>" if caption.present?
      yield
      puts '</div>'
    end

  end


  class PDFMaker

    ### original: 2.4, 2.5
    #def call_hook(hookname)
    #  return if !@config['pdfmaker'].is_a?(Hash) || @config['pdfmaker'][hookname].nil?
    #  hook = File.absolute_path(@config['pdfmaker'][hookname], @basehookdir)
    #  if ENV['REVIEW_SAFE_MODE'].to_i & 1 > 0
    #    warn 'hook configuration is prohibited in safe mode. ignored.'
    #  else
    #    system_or_raise("#{hook} #{Dir.pwd} #{@basehookdir}")
    #  end
    #end
    ### /original

    def call_hook(hookname)
      if ENV['REVIEW_SAFE_MODE'].to_i & 1 > 0
        warn 'hook configuration is prohibited in safe mode. ignored.'
        return
      end
      d = @config['pdfmaker']
      return if d.nil? || !d.is_a?(Hash) || d[hookname].nil?
      ## hookname が文字列の配列なら、それらを全部実行する
      [d[hookname]].flatten.each do |hook|
        script = File.absolute_path(hook, @basehookdir)
        ## 拡張子が .rb なら、rubyコマンドで実行する（ファイルに実行属性がなくてもよい）
        if script.end_with?('.rb')
          ruby = ruby_fullpath()
          ruby = "ruby" unless File.exist?(ruby)
          system_or_raise("#{ruby} #{script} #{Dir.pwd} #{@basehookdir}")
        else
          system_or_raise("#{script} #{Dir.pwd} #{@basehookdir}")
        end
      end
    end

    private
    def ruby_fullpath
      require 'rbconfig'
      c = RbConfig::CONFIG
      return File.join(c['bindir'], c['ruby_install_name']) + c['EXEEXT'].to_s
    end

    public

    ## 文法エラーだけキャッチし、それ以外のエラーはキャッチしないよう変更
    ## （LATEXBuilderで起こったエラーのスタックトレースを表示する）
    def output_chaps(filename, _yamlfile)
      $stderr.puts "compiling #{filename}.tex"
      begin
        @converter.convert(filename + '.re', File.join(@path, filename + '.tex'))
      #rescue => e                       #-
      rescue ApplicationError => e       #+
        @compile_errors = true
        warn "compile error in #{filename}.tex (#{e.class})"
        warn e.message
      end
    end

  end


  ##
  ## 行番号を生成するクラス。
  ##
  ##   gen = LineNumberGenerator.new("1-3&8-10&15-")
  ##   p gen.each.take(15).to_a
  ##     #=> [1, 2, 3, nil, 8, 9, 10, nil, 15, 16, 17, 18, 19, 20, 21]
  ##
  class LineNumberGenerator

    def initialize(arg)
      @ranges = []
      inf = Float::INFINITY
      case arg
      when true        ; @ranges << (1 .. inf)
      when Integer     ; @ranges << (arg .. inf)
      when /\A(\d+)\z/ ; @ranges << (arg.to_i .. inf)
      else
        arg.split('&', -1).each do |str|
          case str
          when /\A\z/
            @ranges << nil
          when /\A(\d+)\z/
            @ranges << ($1.to_i .. $1.to_i)
          when /\A(\d+)\-(\d+)?\z/
            start = $1.to_i
            end_  = $2 ? $2.to_i : inf
            @ranges << (start..end_)
          else
            raise ArgumentError.new("'#{strpat}': invalid lineno format")
          end
        end
      end
    end

    def each(&block)
      return enum_for(:each) unless block_given?
      for range in @ranges
        range.each(&block) if range
        yield nil
      end
      nil
    end

  end


end
