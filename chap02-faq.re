= Re:VIEW Starter FAQ

//abstract{
残念ながら、Re:VIEWでできないことは、Starterでもたいていできません。

このFAQでは、「何ができないか？」を中心に解説します。
//}

#@#//makechaptitlepage[toc=section]

== コメント

=== 範囲コメントはないの？

範囲コメントは、Re:VIEWにはありませんがStarterにはあります。

//emlist[サンプル]{
aaa

@<letitgo>$#@$+++
bbb

ccc
@<letitgo>$#@$---

ddd
//}

//noindent
@<em>{表示結果：}

//resultbegin

aaa

#@+++
bbb

ccc
#@---

ddd

//resultend



 * 「@<code>{#@+++}」から「@<code>{#@---}」までが範囲コメントです。
 * 「@<code>{+}」や「@<code>{-}」の数は3つです。それ以上でも以下でも範囲コメントとは認識されません。
 * 範囲コメントは入れ子にできません。
 * 「@<code>{//embed}」の中では使わないでください。
 * これは実験的な機能なので、将来は仕様が変更したり機能が削除される可能性があります。
   この機能にあまり依存しないようにし、できれば行コメントを使ってください。
   一時的なコメントアウトに限定して使うのがいいでしょう。


=== 行コメントを使ったら勝手に段落が分かれたんだけど、なんで？

Re:VIEWの仕様です。

たとえば次のような5行は、1つの段落になります。

//emlist[サンプル]{
これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！
旧約聖書にある、ソドムとゴモラを滅ぼした天の火だよ。
ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。
//}

//noindent
@<em>{表示結果：}

//resultbegin

これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！
旧約聖書にある、ソドムとゴモラを滅ぼした天の火だよ。
ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。

//resultend



ここで途中の行（3行目）をコメントアウトすると、段落が2つに分かれてしまいます。

//emlist[サンプル]{
これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！
@<letitgo>$#@$#旧約聖書にある、ソドムとゴモラを滅ぼした天の火だよ。
ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。
//}



//noindent
@<em>{表示結果：}

//resultbegin

これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！

ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。

//resultend



なぜかというと、コメントアウトされた箇所が空行として扱われるからです、まるでこのように：

//emlist[サンプル]{
これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！

ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。
//}



段落が分かれてしまうのはこのような理由です。

Re:VIEW開発チームに問い合わせたところ、これがRe:VIEWの仕様であるという回答が返ってきました。
しかしこの仕様だと、段落を分けずに途中の行をコメントアウトする方法がありません。
この仕様は、仕様バグというべきものでしょう。

そこでStarterでは、段落の途中の行をコメントアウトしても段落が分かれないように変更しました。

//noindent
@<em>{表示結果：}

//resultbegin

これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！
#@#旧約聖書にある、ソドムとゴモラを滅ぼした天の火だよ。
ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。

//resultend



こちらのほうが明らかに便利だし、困ることはないと思います。

また「@<code>{//list}」や「@<code>{//terminal}」でも行コメントが有効（つまり読み飛ばされる）ことに注意してください。


== 箇条書き

=== 箇条書きで英単語が勝手に結合するんだけど？

Re:VIEWのバグです@<fn>{zf4y3}。
次のように箇条書きの要素を改行すると、行がすべて連結されてしまいます。

//emlist[サンプル]{
 * aa bb
   cc dd
   ee ff
//}


//noindent
@<em>{表示結果：}

//resultbegin

 * aa bbcc ddee ff

//resultend



これは日本語だと特に問題とはなりませんが、英語だと非常に困ります。

そこでStarterでは、行を連結しないように修正しています。
Starterだと上の例はこのように表示されます。

//emlist[サンプル]{
 * aa bb
   cc dd
   ee ff
//}

//noindent
@<em>{表示結果：}

//resultbegin

 * aa bb
   cc dd
   ee ff

//resultend



//footnote[zf4y3][少なくともRe:VIEW 3.1まではこのバグが存在します。]


=== 順序つき箇条書きに「A.」や「a.」や「i.」を使いたい

Re:VIEWではできません。

Re:VIEWでは、順序つき箇条書きとしては「1. 」や「2. 」という書き方しかサポートしていません。
数字ではなくアルファベットを使おうと「A. 」や「a. 」のようにしても、できません。
Re:VIEWの文法を拡張するしかないです。

なのでStarterでは文法を拡張し、これらの順序つき箇条書きが使えるようにしました。

//emlist[サンプル]{
 - 1. 項目1
 - 2. 項目2

 - A. 項目1
 - B. 項目2

 - a. 項目1
 - b. 項目2
//}

//noindent
@<em>{表示結果：}

//resultbegin

 - 1. 項目1
 - 2. 項目2

 - A. 項目1
 - B. 項目2

 - a. 項目1
 - b. 項目2

//resultend



「@<code>{-}」の前と後、そして「@<code>{1.}」や「@<code>{A.}」や「@<code>{a.}」のあとにも半角空白が必要です。
また半角空白の前の文字列がそのまま出力されるので、「@<code>{(1)}」や「@<code>{A-1:}」などを使えます。

//emlist[サンプル]{
 - (1) 項目1
 - (2) 項目2

 - (A-1) 項目1
 - (A-2) 項目2
//}

//noindent
@<em>{表示結果：}

//resultbegin

 - (1) 項目1
 - (2) 項目2

 - (A-1) 項目1
 - (A-2) 項目2

//resultend




=== 順序つき箇条書きを入れ子にできない？

Re:VIEWではできません。

Re:VIEWでは、順序なし箇条書きは入れ子にできますが、順序つき箇条書きは入れ子にできません。
#@#また順序つき箇条書きの中に順序なし箇条書きを入れ子にすることもできません。
箇条書きの入れ子をインデントで表現するような文法だとよかったのですが、残念ながらRe:VIEWはそのような仕様になっていません。

そこでStarterでは、順序つき箇条書きを入れ子にできる文法を用意しました。
行の先頭に半角空白が必要なことに注意。

//emlist[サンプル]{
 - (A) 大項目
 -- (1) 中項目
 --- (1-a) 小項目
 --- (1-b) 小項目
 -- (2) 中項目
//}

//noindent
@<em>{表示結果：}

//resultbegin

 - (A) 大項目
 -- (1) 中項目
 --- (1-a) 小項目
 --- (1-b) 小項目
 -- (2) 中項目

//resultend



また順序なし箇条書きと順序つき箇条書きを混在できます。
繰り返しますが、行の先頭に半角空白が必要なことに注意。

//emlist[サンプル]{
 * 大項目
 -- a. 中項目
 -- b. 中項目
 *** 小項目
 *** 小項目
//}

//noindent
@<em>{表示結果：}

//resultbegin

 * 大項目
 -- a. 中項目
 -- b. 中項目
 *** 小項目
 *** 小項目

//resultend




=={sec-faq-block} ブロック命令

==={subsec-faq-block1} ブロックの中に別のブロックを入れるとエラーになるよ？

Re:VIEWの仕様です。

Re:VIEWでは、たとえば「@<code>$//note{$ ... @<code>$//}$」の中に「@<code>$//list{$ ... @<code>$//}$」を入れると、エラーになります。
これはかなり困った仕様です。

そこでStarterではこれを改良し、ブロック命令の入れ子ができるようになりました。

//emlist[サンプル]{
@<letitgo>$//$note[■ノートの中にソースコード]{

ノートの中にソースコードを入れるサンプル。

@<letitgo>$//$list[][サンプルコード]{
print("Hello, World!")
@<letitgo>$//$}

@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//note[■ノートの中にソースコード]{

ノートの中にソースコードを入れるサンプル。

//list[][サンプルコード]{
print("Hello, World!")
//}

//}

//resultend



ただし他のブロック命令を含められる（つまり入れ子の外側になれる）のは、今のところ次のブロック命令だけです。

 * @<code>{//note}
 * @<code>{//quote}
 * @<code>{//memo}

これ以外の命令を入れ子対応にしたい場合は、ハッシュタグ「#reviewstarter」をつけてツイートしてください。

また以下のブロック命令は、その性質上他のブロック命令を含めることはできません。

 * @<code>{//list}, @<code>{//emlist}, @<code>{//listnum}, @<code>{//emlist}
 * @<code>{//cmd}, @<code>{//terminal}
 * @<code>{//program}
 * @<code>{//source}

なおStarterでは、以前は「@<code>$====[note]$ ... @<code>$====[/note]$」といった記法を使っていました。この記法は今でも使えますが、ブロック命令の入れ子がサポートされた現在では使う必要もないでしょう。


==={subsec-faq-block2} ブロックの中に箇条書きを入れても反映されないよ？

Re:VIEWの仕様です。

Re:VIEWでは、たとえば「@<code>$//note{$ ... @<code>$//}$」の中に「@<code>{ * 項目1}」のような箇条書きを入れても、箇条書きとして解釈されません。
これはかなり困った仕様です。

そこでStarterではこれを改良し、ブロック命令の中に箇条書きが入れられるようになりました。

//emlist[サンプル]{
@<letitgo>$//$note[■ノートの中に箇条書きやソースコードを入れる例]{

 * 項目1
 * 項目2

@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//note[■ノートの中に箇条書きやソースコードを入れる例]{

 * 項目1
 * 項目2

//}

//resultend



現在のところ、以下のブロック命令で箇条書きをサポートしています。

 * @<code>{//note}
 * @<code>{//quote}
 * @<code>{//memo}

これ以外の命令を入れ子対応にしたい場合は、ハッシュタグ「#reviewstarter」をつけてツイートしてください。


==={subsec-faq-memo} 「@<code>$//info{$ ... @<code>$//}$」のキャプションに「■メモ：」がつくんだけど？

Re:VIEWの仕様です。
「@<code>$//info$」だけでなく、他の「@<code>$//tip$」や「@<code>$//info$」や「@<code>$//warning$」や「@<code>$//important$」や「@<code>$//caution$」や「@<code>$//notice$」も、すべて「■メモ：」になります！

//emlist[サンプル]{
@<letitgo>$//$memo[memoサンプル]{
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//memo[memoサンプル]{
//}

//resultend


//emlist[サンプル]{
@<letitgo>$//$tip[tipサンプル]{
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//tip[tipサンプル]{
//}

//resultend


//emlist[サンプル]{
@<letitgo>$//$info[infoサンプル]{
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//info[infoサンプル]{
//}

//resultend


//emlist[サンプル]{
@<letitgo>$//$warning[warningサンプル]{
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//warning[warningサンプル]{
//}

//resultend


//emlist[サンプル]{
@<letitgo>$//$important[importantサンプル]{
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//important[importantサンプル]{
//}

//resultend


//emlist[サンプル]{
@<letitgo>$//$caution[cautionサンプル]{
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//caution[cautionサンプル]{
//}

//resultend


//emlist[サンプル]{
@<letitgo>$//$notice[noticeサンプル]{
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//notice[noticeサンプル]{
//}

//resultend



わけがわからないよ。

これらのかわりに、Starterでは「@<code>$//note{$ ... @<code>$//}$」を使ってください。
詳しくは@<secref>{chap01-starter|subsec-ext-note}を参照のこと。


== ソースコード

=== ソースコードの見た目が崩れるんだけど？

恐らく、ソースコードの中にタブ文字があることが原因でしょう。

Re:VIEWでは、「@<code>{//list}」などに含まれるタブ文字を半角空白に展開してくれます。
しかしこの展開方法に根本的なバグがあるため、正しく展開してくれません。

たとえば次の例では、1つ目のコメントの前には半角空白を使い、2つ目のコメントの前にはタブ文字を使っています。

//emlist[サンプル]{
@<letitgo>$//$terminal{
$ printf "Hi\n"         # コメントの前に半角空白
#@#$ printf "Hi\n"		# コメントの前にタブ文字
$ printf "Hi\n"         # コメントの前にタブ文字
@<letitgo>$//$}
//}




これをRe:VIEWでコンパイルすると、次のようにタブ文字のある行は表示が崩れてしまいます。
しかもエラーメッセージが出るわけではないので、なかなか気づきません。

//noindent
@<em>{表示結果 (Re:VIEW)}

//resultbegin

//terminal{
$ printf "Hi\n"         # コメントの前に半角空白
#@#$ printf "Hi\n"		# コメントの前にタブ文字
$ printf "Hi\n"            # コメントの前にタブ文字
//}

//resultend



Starterではこの不具合を修正し、タブ文字がある行でも表示が崩れないようにしました。

//noindent
@<em>{表示結果 (Starter)}

//resultbegin

//terminal{
$ printf "Hi\n"         # コメントの前に半角空白
#@#$ printf "Hi\n"		# コメントの前にタブ文字
$ printf "Hi\n"         # コメントの前に半角空白
//}

//resultend



ただし、タブ文字のある行に「@<code>$@<b>{}$」や「@<code>$@<del>{}$」があると、タブ文字を半角空白に正しく展開できません。これは技術的に修正しようがないので、ソースコードではタブ文字より半角空白を使うようにしてください。


=== コラム中のソースコードがページまたぎしてくれないよ？

仕様です。
ブロックと違い、コラム（「@<code>$==[column]$ ... @<code>$==[/column]$」）の中にはブロックを入れられますが、たとえばソースコードを入れた場合、ページをまたぐことができません。
これは@<LaTeX>{}のframed環境による制限です。


=== ソースコードを別ファイルから読み込む方法はないの？

@<href>{https://github.com/kmuto/review/issues/887}によると、このような方法でできるようです。

//list[][別ファイルのソースコード(source/fib1.rb)を読み込む方法]{
@<code>$//$list[fib1][フィボナッチ数列]{
@<code>$@$<include>{source/fib1.rb}
@<code>$//$}
//}

ただし先のリンクにあるように、この方法はundocumentedであり、将来も機能が提供されるかは不明です。
「直近の締切りに間に合えばよい」「バージョンアップはしない」という場合のみ、割り切って使いましょう。
もし使えなくなったとしても、開発チームに苦情を申し立てないようお願いします。


== コンパイル

=== なんで@<LaTeX>{}のコンパイルがいつも3回実行されるの？

Re:VIEWの仕様です。
@<LaTeX>{}のコンパイル中にページ番号が変わってしまうと、古いページ番号のままPDFが生成されてしまいます。
このような事態を防ぐために、3回コンパイルしているのだと思われます@<fn>{wm3r8}。
//footnote[wm3r8][本当ならコンパイルの前後でauxファイルを比較して、ページ番号に差異があればもう一度コンパイルする、という方法が望ましいですが、そこまではしていないようです。]

なお@<LaTeX>{}のコンパイルには1秒程度しかかからないはずです。
3回繰り返しても、5秒未満でしょう。
時間がかかるのはそのあとのPDFへの変換であり、これは画像のサイズやファイル数に比例して時間がかかります。


=== コンパイルに時間かかりすぎ。もっと速くできない？

前の節で説明したように、時間がかかるのは@<LaTeX>{}のコンパイルではなく、そのあとのPDF生成です。
そしてPDF生成は、画像のサイズやファイル数に比例して時間がかかります。

画像のファイル数は減らせないので、かわりに画像のサイズを減らしたり、執筆中だけダミー画像で置き換えるのがいいでしょう。
詳しくは『ワンストップ！技術同人誌を書こう』という本の第8章を参照してください。

または、@<em>{config.yml}の「@<code>$dvioptions:$」の値を調整してください。
「@<code>$-z 1$」だと圧縮率は低いけど速くなり、「@<code>$-z 9$」だと圧縮率は高いけど遅くなります。


== タイトルページ（大扉）

=== タイトルが長いので、指定した箇所で改行したいんだけど？

長いタイトルをつけると、タイトルページ（「大扉」といいます）でタイトルが変な箇所で改行されてしまいます。

表示例：

//embed[latex]{
\begin{center}
  \gtfamily\sffamily\bfseries\ebseries\Huge
  週末なにしてますか?
  忙しいですか?
  金魚すくってもらっていいですか?
\end{center}
\bigskip
//}

この問題に対処するために、Starterではタイトル名に改行を含められるようになっています。
@<em>{config.yml}の「@<code>{booktitle: |-}」という箇所@<fn>{rsjp9}に、タイトル名を複数行で指定してください。
//footnote[rsjp9][「@<code>{|-}」は、YAMLにおいて複数行を記述する記法の1つ（最後の行の改行は捨てられる）。]

//list[][サンプル]{
booktitle: |-
  週末なにしてますか?
  忙しいですか?
  金魚すくってもらっていいですか?
//}

こうすると、タイトルページでも複数行のまま表示されます。

表示例：

//embed[latex]{
\begin{center}
  \gtfamily\sffamily\bfseries\ebseries\Huge
  週末なにしてますか?\\
  忙しいですか?\\
  金魚すくってもらっていいですか?\par
\end{center}
\bigskip
//}

同様に、サブタイトルも複数行で指定できます。

ただし本の最後のページにある「奥付」では、タイトルもサブタイトルも改行されずに表示されます。

Starterではなく、素のRe:VIEWやTechboosterのテンプレートを使っている場合は、@<em>{layouts/layout.tex.erb}を変更します。
変更するまえに、@<em>{layouts/layout.tex.erb}のバックアップをとっておくといいでしょう。

//list[][layouts/layout.tex.erb][ruby]{
....(省略)....
\thispagestyle{empty}
\begin{center}%
  \mbox{} \vskip5zw
   \reviewtitlefont%
    @<del>${\HUGE\bfseries <%= escape_latex(@config.name_of("booktitle")) %> \par}%$
    @<b>${\HUGE\bfseries 週末なにしてますか?\newline%$
    @<b>$                忙しいですか?\newline%$
    @<b>$                金魚すくってもらっていいですか?\par}%$
....(省略)....
//}


=== タイトルぺージがださい。もっとかっこよくならない？

@<LaTeX>{}を使ってるかぎりは難しいでしょう。
それよりもPhotoshopやKeynoteを使ってタイトルページを作るほうが簡単です（@<img>{titlepage-samples}）。

//image[titlepage-samples][Keynoteを使って作成したタイトルページの例]

タイトルページをPhotoshopやKeynoteで作る場合は、@<em>{config.yml}で「@<code>$titlepage: false$」を指定し、タイトルページを生成しないようにしましょう。
そのあと、別途作成したタイトルページのPDFファイルと「@<em>$rake pdf$」で生成されたPDFファイルとを結合してください。

なお奥付もPhotoshopやKeynoteで作る場合は、@<em>{config.yml}に「@<code>$colophon: false$」を指定し、奥付を生成しないようにしてください。
また@<em>{config.yml}には「@<code>$colophon:$」の設定箇所が2箇所あるので、ファイルの下のほうにある該当箇所を変更してください。


== その他

=== 設定ファイルをいじったら、動かなくなった！

Re:VIEWの設定ファイルである@<em>{config.yml}や@<em>{catalog.yml}は、「YAML」というフォーマットで記述されています。
このフォーマットに違反すると、設定ファイルが読み込めなくなるため、エラーになります。

「YAML」のフォーマットについての詳細はGoogle検索してください。
ありがちなミスを以下に挙げておきます。

 * タブ文字を使うと、エラーになります。かわりに半角スペースを使ってください。
 * 全角スペースを使うと、エラーになります。かわりに半角スペースを使ってください。
 * 「@<code>{:}」のあとに半角スペースが必要です。たとえば@<br>{}
   「@<tt>{titlepage:false}」はダメです。@<br>{}
   「@<tt>{titlepage: false}」のように書いてください。
 * 「@<code>{,}」のあとに半角スペースが必要です。たとえば@<br>{}
   「@<code>{texstyle: [reviewmacro,starter,mystyle]}」はダメです。@<br>{}
   「@<code>{texstyle: [reviewmacro, starter, mystyle]}」のように書いてください。
 * インデントが揃ってないと、エラーになります。
   たとえば@<em>{catalog.yml}が次のようになっていると、インデントが揃ってないのでエラーになります。

//list[][「CHAPS:」のインデントが揃ってないのでエラー]{
PREDEF:
  - chap00-preface.re

CHAPS:
   - chap01-starter.re
  - chap02-faq.re

APPENDIX:

POSTDEF:
  - chap99-postscript.re
//}

 * 「@<em>{-}」のあとに半角スペースが必要です。たとえば上の例で@<br>{}「@<code>{- chap01-starter.re}」が@<br>{}「@<code>{-chap01-starter.re}」となっていると、エラーになります。


==={qvtlq} 印刷用と電子用で設定を少し変えるにはどうするの？

印刷所に入稿するためのPDFと、電子用（ダウンロード用）のPDFで、設定を変えたいことがあります。

 * 印刷用のPDFは白黒だけど、電子用のPDFはカラーにしたい。
 * 印刷用のPDFは外側の余白を詰めるけど、電子用ではしない。

このように印刷用のPDFと電子用のPDFで設定を変えたい場合、Re:VIEWでは設定ファイルを継承して別の設定ファイルを作成します。しかしこの機能は設定ファイルを切り替えることしかできないので、使いづらいです。

Starterでは別の設定ファイルを用意しなくても、環境変数「@<code>{$STARTER_TARGET}」を切り替えるだけで印刷用と電子用のPDFを切り替えられます。
詳しくは@<secref>{chap01-starter|bn2iw}を参照してください。

//terminal[][]{
### 印刷用PDFを生成
$ rake pdf    # または STARTER_TARGET=pbook rake pdf

### 電子用PDFを生成
$ STARTER_TARGET=ebook rake pdf
//}

ただしこの機能では、@<LaTeX>{}のスタイルファイル（@<code>{sty/starter.sty}や@<code>{sty/mytextsize.sty}）の中で行える範囲でしか変更はできません。
そのため、たとえば@<code>{config.yml}や@<code>{catalog.yml}や@<code>{layouts/layout.tex.erb}で行うような変更をしたい場合@<fn>{4pxhe}は、自力で頑張る必要があります。
//footnote[4pxhe][たとえば印刷用や電子用とは別にタブレット用を用意し、タブレット用では用紙サイズやフォントサイズを変えるような場合がこれに相当します。以降ではタブレット用を作成する例を紹介しています。]

方針としては、設定ファイルやスタイルファイルを用途に応じて都度生成するといいでしょう。
具体的には次のようにします。

//blankline
//noindent
(1) まず少し変えたいファイルの名前を変更し、末尾に「@<em>{.eruby}」をつけます。

//cmd{
$ mv config.yml         config.yml.eruby
$ mv sty/mytextsize.sty sty/mytextsize.sty.eruby
$ mv sty/starter.sty    sty/starter.sty.eruby
## またはこうでもよい
$ mv config.yml{,.eruby}
$ mv sty/mytextsize.sty{,.eruby}
$ mv sty/starter.sty{,.eruby}
//}

//noindent
(2) 次に、それらのファイルに次のような条件分岐を埋め込みます。

//source[config.yml.eruby]{
....(省略)....
@<b>$<% if buildmode == 'printing'   # 印刷向け %>$
texdocumentclass: ["jsbook", "uplatex,papersize,twoside,b5j,10pt,openright"]
@<b>$<% elsif buildmode == 'tablet'  # タブレット向け %>$
texdocumentclass: ["jsbook", "uplatex,papersize,oneside,a5j,10pt,openany"]
@<b>$<% else abort "error: buildmode=#{buildmode.inspect}" %>$
@<b>$<% end %>$
....(省略)....
@<b>$<% if buildmode == 'printing'   # 印刷向け %>$
dvioptions: "-d 5 -z 3"  # 速度優先
@<b>$<% elsif buildmode == 'tablet'  # タブレット向け %>$
dvioptions: "-d 5 -z 9"  # 圧縮率優先
@<b>$<% else abort "error: buildmode=#{buildmode.inspect}" %>$
@<b>$<% end %>$
....(省略)....
//}

//source[sty/mytextsize.sty.eruby]{
@<b>$<%$
@<b>$if buildmode == 'printing'   # 印刷向け$
@<b>$  textwidth  = '42zw'$
@<b>$  sidemargin = '1zw'$
@<b>$elsif buildmode == 'tablet'  # タブレット向け$
@<b>$  textwidth  = '40zw'$
@<b>$  sidemargin = '0zw'$
@<b>$else abort "error: buildmode=#{buildmode.inspect}"$
@<b>$end$
@<b>$%>$
....(省略)....
\setlength{\textwidth}{@<b>$<%= textwidth %>$}
....(省略)....
\addtolength{\oddsidemargin}{@<b>$<%= sidemargin %>$}
\addtolength{\evensidemargin}{-@<b>$<%= sidemargin %>$}
....(省略)....
//}

//source[sty/starter.sty.eruby]{
....(省略)....
@<b>$<% if buildmode == 'printing'   # 印刷向け %>$
\definecolor{starter@chaptercolor}{gray}{0.40}  % 0.0: black, 1.0: white
\definecolor{starter@sectioncolor}{gray}{0.40}
\definecolor{starter@captioncolor}{gray}{0.40}
\definecolor{starter@quotecolor}{gray}{0.40}
@<b>$<% elsif buildmode == 'tablet'  # タブレット向け %>$
\definecolor{starter@chaptercolor}{HTML}{20B2AA} % lightseagreen
\definecolor{starter@sectioncolor}{HTML}{20B2AA} % lightseagreen
\definecolor{starter@captioncolor}{HTML}{FFA500} % orange
\definecolor{starter@quotecolor}{HTML}{E6E6FA}   % lavender
@<b>$<% else abort "error: buildmode=#{buildmode.inspect}" %>$
@<b>$<% end %>$
....(省略)....
@<b>$<% if buildmode == 'printing'   # 印刷向け %>$
\hypersetup{colorlinks=true,linkcolor=black} % 黒
@<b>$<% elsif buildmode == 'tablet'  # タブレット向け %>$
\hypersetup{colorlinks=true,linkcolor=blue}  % 青
@<b>$<% else abort "error: buildmode=#{buildmode.inspect}" %>$
@<b>$<% end %>$
//}

//noindent
(3) ファイルを生成するRakeタスクを定義します。
ここまでが準備です。

//source[lib/tasks/mytasks.rake]{
def render_eruby_files(param)   # 要 Ruby >= 2.2
  Dir.glob('**/*.eruby').each do |erubyfile|
    origfile = erubyfile.sub(/\.eruby$/, '')
    sh "erb -T 2 '#{param}' #{erubyfile} > #{origfile}"
  end
end


namespace :setup do

  desc "*印刷用に設定 (B5, 10pt, mono)"
  task :printing do
    render_eruby_files('buildmode=printing')
  end

  desc "*タブレット用に設定 (A5, 10pt, color)"
  task :tablet do
    render_eruby_files('buildmode=tablet')
  end

end
//}

//noindent
(4)「@<em>{rake setup::printing}」または「@<em>{rake setup::tablet}」を実行します。
すると、@<em>{config.yml}と@<em>{sty/mytextsize.sty}と@<em>{sty/starter.sty}が生成されます。
そのあとで「@<em>{rake pdf}」を実行すれば、用途に応じたPDFが生成されます。

//cmd{
$ @<b>{rake setup::printing  # 印刷用}
$ rake pdf
$ mv mybook.pdf mybook_printing.pdf

$ @<b>{rake setup::tablet    # タブレット用}
$ rake pdf
$ mv mybook.pdf mybook_tablet.pdf
//}


=== @<LaTeX>{}のスタイルファイルから環境変数を読める？

Starterでは、名前が「$<code>{STARTER_}」で始まる環境変数を@<LaTeX>{}のスタイルファイルから参照できます。

たとえば「@<code>{STARTER_FOO_BAR}」という環境変数を設定すると、@<code>{sty/mystyle.sty}や@<code>{sty/starter.sty}では「@<code>{\STARTER@FOO@BAR}」という名前で参照できます。
想像がつくと思いますが、環境変数名の「@<code>{_}」は「@<code>{@}」に変換されます。

//terminal[][環境変数を設定する例(macOS, UNIX)]{
$ export STARTER_FOO_BAR="foobar"
//}

//list[][環境変数を参照する例]{
%% ファイル：sty/mystyle.sty
\newcommand\foobar[0]{%             % 引数なしコマンドを定義
  \@ifundefined{STARTER@FOO@BAR}{%  % 未定義なら
    foobar%                         % デフォルト値を使う
  }{%                               % 定義済みなら
    \STARTER@FOO@BAR%               % その値を使う
  }%
}
//}

この機能を使うと、出力や挙動を少し変更したい場合に環境変数でコントロールできます。
また値の中に「@<code>{$}」や「@<code>{\\}」が入っていてもエスケープはしないので注意してください。
