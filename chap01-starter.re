= Re:VIEW Starterの独自機能

//abstract{
素のRe:VIEWと比べて、Re:VIEW Starter（以下「Starter」とする）はいろんな機能強化やバグフィックスをしています。
この章では、それらについて解説します@<fn>{jmoh7}。

また本章ではRe:VIEWの機能や@<LaTeX>{}の用語が説明なく使われます。
これらが分からなければ読み飛ばして、分かる箇所だけ読んでください。
//}
//footnote[jmoh7][本章では、Re:VIEWや@<LaTeX>{}についての説明はしません。Re:VIEWの書き方についてはマニュアル（@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md}）やチートシート（@<href>{https://qiita.com/froakie0021/items/b0f4ba5f242bbd571d4e}）を参照してください。]

#@#//makechaptitlepage[toc=section]


=={sec-ext} 原稿本文を書くための機能


=== 強調

 * 「@<code>$@<b>{...}$」は、明朝体のまま太字になります（Re:VIEWのデフォルト）。
 * 「@<code>$@<em>{...}$」は、ゴシック体になります（Starter拡張）。
 * 「@<code>$@<strong>{...}$」は、太字のゴシック体になります（Starter拡張）。
 * 「@<code>$@<B>{...}$」は、「@<code>$@<strong>{...}$」のショートカットです（Starter拡張）。

//emlist[サンプル]{
いろはfghij  @<letitgo>$@$<b>{いろはfghij}  @<letitgo>$@$<em>{いろはfghij}  @<letitgo>$@$<strong>{いろはfghij}
@<letitgo>$@$<B>{いろはfghij}
//}

//noindent
@<em>{表示結果：}

//resultbegin

いろはfghij  @<b>{いろはfghij}  @<em>{いろはfghij}  @<strong>{いろはfghij}
@<B>{いろはfghij}

//resultend



なおソースコードの一部を太字にしたいときは、「@<code>$@<strong>{...}$」ではなく「@<code>$@<b>{...}$」を使ってください。
なぜなら「@<code>$@<strong>{...}$」だとゴシック体になってしまうのに対し、「@<code>$@<b>{...}$」だとタイプライタ体のまま太字になるからです。

//emlist[サンプル]{
@<letitgo>$//$emlist{
タイプライタ体（通常）： 0123456789 ijkl IJKL !"$%&()*,-./:;?@[\]`|~
タイプライタ体（太字）： @<letitgo>$@$<b>{0123456789 ijkl IJKL !"$%&()*,-./:;?@[\\]`|~}
ゴシック体　　（太字）： @<letitgo>$@$<strong>{0123456789 ijkl IJKL !"$%&()*,-./:;?@[\\]`|~}
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//emlist{
タイプライタ体（通常）： 0123456789 ijkl IJKL !"$%&()*,-./:;?@[\]`|~
タイプライタ体（太字）： @<b>{0123456789 ijkl IJKL !"$%&()*,-./:;?@[\\]`|~}
ゴシック体　　（太字）： @<strong>{0123456789 ijkl IJKL !"$%&()*,-./:;?@[\\]`|~}
//}

//resultend




==={subsec-olist} 番号つきリストの機能強化

Re:VIEWでは番号つきリストを次のように書きます。

//emlist[サンプル]{
 1. XXX
 2. YYY
 3. ZZZ
//}

//noindent
@<em>{表示結果：}

//resultbegin

 1. XXX
 2. YYY
 3. ZZZ

//resultend



この書き方には次の欠点があります。

 * 数字の番号はつきますが、「A.」や「a.」などは使えません。
 * また番号つきリストを入れ子にできません。

そこでStarterでは別の書き方を用意しました。

//emlist[サンプル]{
数字による番号つきリスト

 - 1. XXX
 - 2. YYY
 - 3. ZZZ

大文字による番号つきリスト

 - A. XXX
 - B. YYY
 - C. ZZZ

小文字による番号つきリスト

 - a. XXX
 - b. YYY
 - c. ZZZ
//}

//noindent
@<em>{表示結果：}

//resultbegin

数字による番号つきリスト

 - 1. XXX
 - 2. YYY
 - 3. ZZZ

大文字による番号つきリスト

 - A. XXX
 - B. YYY
 - C. ZZZ

小文字による番号つきリスト

 - a. XXX
 - b. YYY
 - c. ZZZ

//resultend



「1.」や「A.」や「a.」のあとに必ず半角空白が必要です。
実は半角空白があれば、その前に書いた文字列がそのまま出力されます。
なので次のような書き方もできます。
箇条書きのように見えますが、「・」がついてないことに注意してください。

//emlist[サンプル]{
 - (A) 項目A
 - (B) 項目B
 - (C) 項目C

 - 甲: 山田太郎
 - 乙: 佐藤花子
//}

//noindent
@<em>{表示結果：}

//resultbegin

 - (A) 項目A
 - (B) 項目B
 - (C) 項目C

 - 甲: 山田太郎
 - 乙: 佐藤花子

//resultend



また入れ子にできます。

//emlist[サンプル]{
 - (A) 作業A
 -- (A-1) 作業A-1
 -- (A-2) 作業A-2
//}

//noindent
@<em>{表示結果：}

//resultbegin

 - (A) 作業A
 -- (A-1) 作業A-1
 -- (A-2) 作業A-2

//resultend



箇条書きとの混在もできます。

//emlist[サンプル]{
番号つきリストの中に箇条書き

 - A. XXX
 ** xxx
 ** xxx

箇条書きの中に番号つきリスト

 * XXXX
 -- a. xxx
 -- b. xxx
//}

//noindent
@<em>{表示結果：}

//resultbegin

番号つきリストの中に箇条書き

 - A. XXX
 ** xxx
 ** xxx

箇条書きの中に番号つきリスト

 * XXXX
 -- a. xxx
 -- b. xxx

//resultend



なお数字や大文字や小文字の順番を補正するようなことはしません。
たとえば「1.」を連続して書けばそれがそのまま出力されます。

//emlist[サンプル]{
 - 1. XXX
 - 1. YYY
 - 1. ZZZ
//}

//noindent
@<em>{表示結果：}

//resultbegin

 - 1. XXX
 - 1. YYY
 - 1. ZZZ

//resultend




==={subsec-ext-note} ノート

「@<code>$//note[$...@<code>$]{$ ... @<code>$//}$」で、付加情報や注意書きのブロックが書けます。
Re:VIEW標準と比べると、デザインを大きく変更していることと、段落の先頭は1文字分インデントされる点が違います。

//emlist[サンプル]{
@<letitgo>$//$note[■注意：印刷所の締切り日を確かめること]{
印刷所の締切りは、技術書典のようなイベントの本番当日よりずっと前です。
通常は約1週間前、また割引きを受けようと思ったら約2週間前が締切りです。
実際の締切り日は印刷所ごとに違うので、必ず確認しておきましょう。

また他の人に原稿のレビューを頼む場合は、さらに1〜2週間必要です。
これも忘れやすいので注意しましょう。
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//note[■注意：印刷所の締切り日を確かめること]{
印刷所の締切りは、技術書典のようなイベントの本番当日よりずっと前です。
通常は約1週間前、また割引きを受けようと思ったら約2週間前が締切りです。
実際の締切り日は印刷所ごとに違うので、必ず確認しておきましょう。

また他の人に原稿のレビューを頼む場合は、さらに1〜2週間必要です。
これも忘れやすいので注意しましょう。
//}

//resultend



実はRe:VIEWでは、ノートの中に箇条書きや他のブロック命令を含められません。これは技術同人誌や書籍の執筆において、大変困る欠点です。

なのでStarterではこれを解決し、ノートの中に箇条書きや他のブロック命令を含められるようにしました@<fn>{wosu0}@<fn>{mg7ep}。

//footnote[wosu0][以前はこれができなかったので、「@<code>$====[note\]$ ... @<code>$====[/note\]$」という別の記法が必要でした。今でもこの記法は有効ですが、もう使う必要はありません。]
//footnote[mg7ep][昔はノート中のプログラム（「@<code>$//emlist$」や「@<code>$//cmd$」）やターミナル（「@<code>$//terminal$」）がページをまたげないという制限がありましたが、現在はその制限はなくなりました。]

//emlist[サンプル]{
@<b>|//note[■ノートサンプル]{|

箇条書きを含める例@<letitgo>$@$<fn>{t71o9}。

 * エマ
 * レイ
 * ノーマン

@<letitgo>$//$footnote[t71o9][ノートの中に脚注を含めるサンプル。]

他のブロックを含める例。

@<letitgo>$//$emlist[RubyでHello]{
def hello(name)
  print("Hello, #{name}!\n")
end
@<letitgo>$//$}

@<letitgo>$//$cmd[UNIXでHello]{
$ echo Hello
Hello
@<letitgo>$//$}

@<b>|//}|
//}

//noindent
@<em>{表示結果：}

//resultbegin

//note[■ノートサンプル]{

箇条書きを含める例@<fn>{t71o9}。

 * エマ
 * レイ
 * ノーマン

//footnote[t71o9][ノートの中に脚注を含めるサンプル。]

他のブロックを含める例。

//emlist[RubyでHello]{
def hello(name)
  print("Hello, #{name}!\n")
end
//}

//cmd[UNIXでHello]{
$ echo Hello
Hello
//}

//}

//resultend



なお「@<code>$//note$」機能はRe:VIEWの標準機能であり、Starterはそれを上書きしています。
実はRe:VIEWの標準のままだと、次のような表示になります。

//emlist[サンプル]{
@<letitgo>$//$note[印刷所の締切り日を確かめること]{
印刷所の締切りは、技術書典のようなイベントの本番当日よりずっと前です。
通常は約1週間前、また割引きを受けようと思ったら約2週間前が締切りです。
実際の締切り日は印刷所ごとに違うので、必ず確認しておきましょう。

また他の人に原稿のレビューを頼む場合は、さらに1〜2週間必要です。
これも忘れやすいので注意しましょう。
@<letitgo>$//$}
//}

//noindent
@<em>{表示例（Re:VIEWのデフォルト）：}

//resultbegin

//memo[印刷所の締切り日を確かめること]{
印刷所の締切りは、技術書典のようなイベントの本番当日よりずっと前です。
通常は約1週間前、また割引きを受けようと思ったら約2週間前が締切りです。
実際の締切り日は印刷所ごとに違うので、必ず確認しておきましょう。

また他の人に原稿のレビューを頼む場合は、さらに1〜2週間必要です。
これも忘れやすいので注意しましょう。
//}

//resultend



段落の先頭がインデントされてないことが分かります。
また、ノート（「@<code>$//note$」）なのになぜかキャプションが「■メモ：」になってる！
おかしいですよね。
詳しくは@<secref>{chap02-faq|subsec-faq-memo}を参照のこと。


=== プログラムコード用のコマンドを統一

Re:VIEWでは、プログラムコードを書くためのブロックコマンドが複数あります。

 : @<code>{//list[}@<i>{ID}@<code>{][}@<i>{caption}@<code>{][}@<i>{lang}@<code>{]}
	リスト番号あり、行番号なし
 : @<code>{//emlist[}@<i>{caption}@<code>{][}@<i>{lang}@<code>{]}
	リスト番号なし、行番号なし
 : @<code>{//listnum[}@<i>{ID}@<code>{][}@<i>{caption}@<code>{][}@<i>{lang}@<code>{]}
	リスト番号あり、行番号あり
 : @<code>{//emlistnum[}@<i>{caption}@<code>{][}@<i>{lang}@<code>{]}
	リスト番号なし、行番号あり

Starterでは、これらをすべて「@<code>$//list[][][]$」に統一しました。
それ以外のコマンドは、実質的に「@<code>$//list[][][]$」へのエイリアスとなります@<fn>{78vwj}。

//footnote[78vwj][「@<code>{//emlist}」や「@<code>{listnum}」が使えなくなったわけではありません。これらも引き続き使えますが、動作は「@<code>{//list}」を呼び出すだけになりました。]

 * 第1引数が空だと、「リストX.X:」のような番号がつきません。
   つまり「@<code>$//emlist$」と同じです。
 * 第3引数に「@<code>{lineno=on}」をつけると、行番号がつきます。
   つまり「@<code>$//listnum$」と同じです。
 * 第1引数を空にし、第3引数に「@<code>{lineno=on}」をつけると、リスト番号がつかず行番号がつきます。
   つまり「@<code>$//emlistnum$」と同じです。

//emlist[サンプル]{
@<b>|//list[4k2ny][リスト番号あり]|{
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2)
end
@<letitgo>$//$}

@<b>|//list[][リスト番号なし]|{
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2)
end
@<letitgo>$//$}

@<b>|//list[970bl][リスト番号あり、行番号あり][lineno=on]|{
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2)
end
@<letitgo>$//$}

@<b>|//list[][リスト番号なし、行番号あり][lineno=on]|{
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2)
end
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[4k2ny][リスト番号あり]{
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2)
end
//}

//list[][リスト番号なし]{
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2)
end
//}

//list[970bl][リスト番号あり、行番号あり][lineno=on]{
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2)
end
//}

//list[][リスト番号なし、行番号あり][lineno=on]{
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2)
end
//}

//resultend



リスト番号もキャプションも行番号もつけない場合は、すべての引数を省略して「@<code>$//list{ ... //}$」のように書けます。
この書き方はRe:VIEWではエラーになりますが、Starterではエラーになりません。

//emlist[サンプル]{
@<b>|//list|{
function fib(n) {
    return n <= 1 ? n : fib(n-1) + fib(n-2);
}
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list{
function fib(n) {
    return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//resultend



また「@<code>{//list}」の第3引数には、以下のオプションが指定できます。

 : @<code>$fold={on|off}$
	長い行を自動で折り返します（詳しくは後述）。
	デフォルトは@<code>{on}。
 : @<code>$foldmark={on|off}$
	折り返したことを表す、小さな記号をつけます。
	デフォルトは@<code>{on}。
 : @<code>$eolmark={on|off}$
	すべての行末に、行末であることを表す小さな記号をつけます。
	「@<code>$foldmark=on$」のかわりに使うことを想定していますが、両方を@<code>{on}にしても使えます。
	デフォルトは@<code>{off}。
 : @<code>$lineno={on|off|$@<i>$integer$@<code>$|$@<i>$pattern$@<code>$}$
	行番号をつけます。
	行番号は1から始まりますが、整数を指定するとそれが最初の行番号になります。
	またより複雑なパターンも指定できます（後述）。
	デフォルトは@<code>{off}。
 : @<code>$linenowidth=$@<i>$integer$
	行番号の桁数を指定します（詳しくは後述）。
	0だと自動計算します。
	値が0以上だと、行番号の分だけプログラムコードの表示幅が狭くなります。
	値がマイナスだと行番号はページの右余白に書かれるので、プログラムコードの表示幅が狭くなりません。
	デフォルトは@<code>{-1}。
 : @<code>$lang=$@<i>$name$
	プログラミング言語名を表します。
	デフォルトはなし。

いくつか補足事項があります。

 * 複数のオプションを指定するときは、「@<code>{,}」で区切ってください。
   たとえば「@<code>{//list[][][eolmark=on,lineno=on,linenowidth=3]}」のようにします。
 * オプションの名前だけを指定して値を省略すると、「@<code>{on}」を指定したとみなされます。
   たとえば「@<code>{lineno}」は「@<code>{lineno=on}」と同じです。
 * 「@<code>$lang=$@<i>$name$」を指定してもコードハイライトはできません。
   この制限は将来改善される予定ですが、時期は未定です。
 * 「@<code>$lang=$@<i>$name$」の場合は、省略形は「@<code>$lang$」ではなく「@<i>$name$」です@<fn>{auf8z}。
   またこの省略ができるのは、第3引数の最初のオプションに指定した場合だけです。
   つまり、「@<code>$ruby,lineno=1$」はOKだけど「@<code>$lineno=1,ruby$」はエラーになります。

//list[][]{
@<letitgo>{}これはOK
@<letitgo>{}//list[][][@<b>{ruby},lineno=1]{
@<letitgo>{}//}

@<letitgo>{}これはエラー
@<letitgo>{}//list[][][lineno=1,@<b>{ruby}]{
@<letitgo>{}//}

@<letitgo>{}これはOK
@<letitgo>{}//list[][][lineno=1,@<b>{lang=ruby}]{
@<letitgo>{}//}
//}

//footnote[auf8z][これはRe:VIEWとの互換性を保つために仕方なく決めた仕様なので、できれば「@<code>$lang={name}$」と省略せずに書いてください。この省略のせいでオプション名が間違っていても言語名とみなされてしまうので注意してください。]


=== ターミナル画面を表す「@<code>$//terminal$」ブロック

Starterでは、ターミナル画面用の新しいブロック命令「@<code>$//terminal{$ ... @<code>$//}$」を用意しました@<fn>{mthjy}。
これは「@<code>$//cmd{$ ... @<code>$//}$」とよく似ていますが、オプションの指定方法が「@<code>$//list{$ ... @<code>$//}$」と同じになっています。

//footnote[mthjy][@<code>$//terminal$命令の定義は@<code>$lib/hooks/monkeypatch.rb$で行っています。]

次の例を見てください。

 * 「@<code>$//cmd$」はオプション引数としてキャプションしか取れません。
   そのためリスト番号をつけられないし、行番号もつけられません。

//emlist[サンプル]{
@<b>|//cmd[キャプション]|{
$ echo foobar
foobar
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//cmd[キャプション]{
$ echo foobar
foobar
//}

//resultend



 * 「@<code>$//terminal$」はオプション引数が「@<code>$//list$」と同じです。
   そのためリスト番号をつけたり、行番号をつけることが簡単にできます。

//emlist[サンプル]{
@<b>|//terminal[id6789][キャプション][lineno=on]|{
$ echo foobar
foobar
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//terminal[id6789][キャプション][lineno=on]{
$ echo foobar
foobar
//}

//resultend



なおStarterでは、「@<code>{//cmd}」は実質的に「@<code>{//terminal}」を呼び出しているだけです。
なので上で説明したこと以外では、両者の機能は同じです。


=== プログラムコード中の長い行を自動的に折り返す

Starterでは、プログラムやターミナルの中の長い行を自動的に折り返します。

//emlist[サンプル]{
@<letitgo>$//$list[][長い行を含むプログラム例]{
data = <<HERE
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
HERE
@<letitgo>$//$}

@<letitgo>$//$terminal[][長い行を含む出力例]{
$ ruby foo/bar/baz/testprog.rb
foo/bar/baz/testprog.rb:11:in `func1': undefined local variable or method `aaabbbccc' for main:Object (NameError)
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[][長い行を含むプログラム例]{
data = <<HERE
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
HERE
//}

//terminal[][長い行を含む出力例]{
$ ruby foo/bar/baz/testprog.rb
foo/bar/baz/testprog.rb:11:in `func1': undefined local variable or method `aaabbbccc' for main:Object (NameError)
//}

//resultend



いくつか注意事項があります。

 * 折り返した行には、折り返したことを表す小さな記号がつきます。
   これをつけなくない場合は、「@<code>{//list}」や「@<code>{//terminal}」の第3引数に「@<code>{foldmark=off}」を指定してください。
 * 折り返すはずの箇所が日本語の場合、折り返しを表す記号が挿入されません@<fn>{wilge}。
   日本語の途中で折り返しをしたい場合は、手動で「@<code>$@<foldhere>{}$」を挿入してください。
 * 折り返し機能によって何らかの問題が発生したら、「@<code>{//list}」や「@<code>{//terminal}」の第3引数に「@<code>{fold=off}」を指定して折り返し機能をオフにしてください。
   これは原因の切り分けに役立つでしょう。

//footnote[wilge][英数字なら折り返し改行される位置にハイフンが入ります。このハイフンを強引に置き換えることで、折り返し記号を挿入しています。しかしpLaTeXでは日本語だとハイフンが入らないため、折り返し記号も挿入されません。これの解決は難しそうなので、別の方法を模索中。]

//note[折り返し記号のかわりに行末記号]{

折り返し箇所が日本語だと折り返し記号がうまく挿入されません。
かといって手動で「@<code>$@<foldhere>{}$」を挿入するのも面倒です。

そのような場合は、折り返し記号をオフにし、かわりに行末記号を入れることを検討してください。

次がその例です。折り返し記号はありませんが、行末記号があるので、行末記号がない箇所は折り返しされていることがわかります。

//emlist[サンプル]{
@<letitgo>$//$list[][]@<b>|[foldmark=off,eolmark=on]|{
def emergency()
  abort '深刻なエラーが発生しました。今すぐシステム管理者に連絡して、対処方法を仰いでください。'
end
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[][][foldmark=off,eolmark=on]{
def emergency()
  abort '深刻なエラーが発生しました。今すぐシステム管理者に連絡して、対処方法を仰いでください。'
end
//}

//resultend



//}


=== プログラムやターミナルの行番号を出力

Starterでは、プログラムやターミナルに行番号をつけられます。

//emlist[サンプル]{
@<letitgo>$//$list[][][@<b>|lineno=on|]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[][][lineno=on]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//resultend



正の整数を指定すると、最初の行番号になります。

//emlist[サンプル]{
@<letitgo>$//$list[][][@<b>|lineno=98|]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[][][lineno=98]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//resultend



行番号の桁数を指定すると、行番号が余白ではなく内側に表示されます。
その分、プログラムコードの表示幅が狭くなってしまいます。

//emlist[サンプル]{
@<letitgo>$//$list[][][lineno=98,@<b>|linenowidth=5|]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[][][lineno=98,linenowidth=5]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//resultend



行番号が灰色で表示されていることにも注目してください。
こうすることで、行番号とプログラムコードとの見分けがつきやすくなっています。

行番号の桁数に@<code>{0}を指定すると、表示幅を自動計算します。

//emlist[サンプル]{
@<letitgo>$//$list[][][lineno=98,@<b>|linenowidth=0|]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[][][lineno=98,linenowidth=0]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//resultend



長い行が折り返されたときは、折り返された行が左端からは始まらず、行番号の表示幅の分だけインデントされます。

//emlist[サンプル]{
@<letitgo>$//$list[][][lineno=1,linenowidth=2]{
data = <<HERE
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
HERE
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[][][lineno=1,linenowidth=2]{
data = <<HERE
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
HERE
//}

//resultend



行番号を表す、より複雑なパターンを指定できます。

 * 「@<code>{1-10}」なら、1行目から10行目まで
 * 「@<code>{1-10&15-18}」なら、1行目から10行目までと、1行空けて15行目から18行目まで
 * 「@<code>{1-10&15-}」なら、1行目から10行目までと、1行空けて15行目から最終行まで

サンプルを見ればどういうことか分かるでしょう。

//emlist[サンプル]{
@<letitgo>$//$list[][][@<b>|lineno=10&18-20&25-|]{
class Hello
  ...(省略)...
  def initialize(name)
    @name = name
  end
  ...(省略)...
  def hello
    print("Hello #{@name}\n")
  end

end
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[][][lineno=10&18-20&25-]{
class Hello
  ...(省略)...
  def initialize(name)
    @name = name
  end
  ...(省略)...
  def hello
    print("Hello #{@name}\n")
  end

end
//}

//resultend





=== ラベル指定なしでリスト番号を出力

リスト番号つきでソースコードを表示する場合、「@<code>$//list$」の第1引数にラベルを指定します。

//emlist[サンプル]{
@<letitgo>$//$list@<b>|[samplecode3]|[サンプル]{
puts "Hello"
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[samplecode3][サンプル]{
puts "Hello"
//}

//resultend



このラベルは、重複しないよう気をつけなければいけません。
リスト番号をあとから参照する場合は重複しないことが必要ですが、単にリスト番号をつけたい場合は重複しないラベルを選ぶのは面倒です。
特に、すべてのソースコードにリスト番号をつけようと思った場合はかなりの手間になります。

そこでStarterでは、「@<code>$//list[?]$」のように第1引数を「@<code>$?$」とするだけで、ラベルとしてランダムな文字列が割り当てられるようにしました@<fn>{w90w6}。
これにより、すべてのソースコードにリスト番号をつけるのが大幅に簡単になりました。
//footnote[w90w6][実装は@<em>{lib/hooks/monkeypatch.rb}の中で@<em>{ReVIEW::Book::Compilable#content()}を上書きして実現しています。]

//emlist[サンプル]{
@<letitgo>$//$list[@<b>|?|][サンプル]{
puts "Hello"
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[?][サンプル]{
puts "Hello"
//}

//resultend



この機能をサポートしているのは、次のブロック命令です。

 * @<code>$//list[?][$@<i>$caption$@<code>$]$ ... @<code>$//}$
 * @<code>$//listnum[?][$@<i>$caption$@<code>$]$ ... @<code>$//}$
 * @<code>$//terminal[?][$@<i>$caption$@<code>$]$ ... @<code>$//}$


=== キャプションなしでもリスト番号だけを出力

Re:VIEWでは、キャプションがないとリスト番号もつかない仕様です。
つまり「@<code>{//list[][]}」の第1引数を指定しても、第2引数が空ならリスト番号はつきません。
キャプションなしでリスト番号だけをつけたい場合は、第2引数に全角空白を入れます。

Starterではこの仕様を変更し、第1引数が指定してあれば第2引数が空（つまりキャプションが空）でもリスト番号をつけるようにしています。
こちらのほうが仕様として自然です。

//emlist[サンプル]{
@<b>|//list[test7][]|{
puts "Hello"
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//list[test7][]{
puts "Hello"
//}

//resultend




=== プログラムのキャプション直後の改ページを抑制

Re:VIEWでは、プログラムやターミナルのキャプション（説明）直後に改ページされてしまうことがあります（@<img>{caption_pagebreak}）。
もしこうなると、キャプションが何を説明しているのか分かりにくくなります。
//image[caption_pagebreak][キャプションの直後で改ページされた例][scale=0.8]

Starterではこれを改善し、キャプションの直後では改ページを起こさないようにしました@<fn>{6yw2g}。
かわりにキャプションの直前で改ページされます。
//footnote[6yw2g][これは@<LaTeX>{}の@<em>{needspace.sty}で実現しています。]

ただし同じページに脚注が複数行あると、判定を間違えてキャプション直後に改ページされることがあります。
これは現在の制限事項です。
経験則として、キャプションの前の文章を増やすとなぜか治ることが多いです。


=== コラム内の脚注

Re:VIEWでは、コラムの中に書いた脚注が消えることがあります。
たとえば次のように書いた場合は、脚注が消えます。

//emlist[コラム内の脚注が消えるサンプル]{
==[column] サンプル
本文本文@<code>$@$<fn>{xxx1}本文本文。

@<letitgo>$//$footnote[xxx1][脚注脚注脚注。]
//}

こうではなく、次のようにコラムを明示的に閉じてから脚注を書くと、消えずに表示されます。

//emlist[コラム内の脚注が消えないサンプル]{
==[column] サンプル
本文本文@<code>$@$<fn>{xxx1}本文本文。

@<b>$==[/column]$

@<letitgo>$//$footnote[xxx1][脚注脚注脚注。]
//}

Starterではこの問題に対処するために、前者のように書かれた場合でも、後者のように自動変換します。

変換はスクリプト@<em>{lib/hooks/beforetexcompile.rb}が行います。
設定ファイルである@<em>{config.yml}に「@<code>$hook_beforetexcompile: [lib/hooks/beforetexcompile.rb]$」という設定を追加しているため、@<LaTeX>{}コマンドでコンパイルされる前にこのスクリプトが実行されるようになっています。


=== 右寄せ、左寄せ、センタリング

Starterでは、右寄せや左寄せやセンタリングをする機能を追加しました。

//emlist[サンプル]{
@<letitgo>$//$textright{
右寄せのサンプル
@<letitgo>$//$}
@<letitgo>$//$textleft{
左寄せのサンプル
@<letitgo>$//$}
@<letitgo>$//$textcenter{
センタリングのサンプル
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//textright{
右寄せのサンプル
//}
//textleft{
左寄せのサンプル
//}
//textcenter{
センタリングのサンプル
//}

//resultend



しかし、実はRe:VIEWにも右寄せとセンタリングの機能があることが判明しました。
今後はこちらを使うのがいいでしょう@<fn>{b9jz8}。
//footnote[b9jz8][ただし@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md}には載ってないので、undocumentedな機能です。将来は変更されるかもしれません。]

//emlist[サンプル]{
@<letitgo>$//$flushright{
右寄せのサンプル
@<letitgo>$//$}
@<letitgo>$//$centering{
センタリングのサンプル
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//flushright{
右寄せのサンプル
//}
//centering{
センタリングのサンプル
//}

//resultend




=== 章の概要

Starterでは、章(Chapter)の概要を表す「@<code>$//abstract{$ ... @<code>$//}$」を用意しています。
#@#これは、@<LaTeX>{}の「@<em>$abstract$」環境と同等です。

//emlist[サンプル]{
@<letitgo>$//$abstract{
この章では、XXXのXXXという機能について説明します。
この機能を理解することで、あとの章が理解できるようになります。
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//abstract{
この章では、XXXのXXXという機能について説明します。
この機能を理解することで、あとの章が理解できるようになります。
//}

//resultend



本文と違う見た目にするために、デフォルトでは左右に全角2.5文字文の余白を追加し、かつゴシック体で表示します。
デザインを変更する場合は、@<em>{sty/starter.sty}で「@<code>$\newenvironment{starterabstract}$」を探し、変更してください。

なおこれとよく似た機能として、Re:VIEWには導入文（リード文）を表す「@<code>$//lead{$ ... @<code>$//}$」が標準で用意されています。
これは主に、詩や物語や聖書からの引用を表すのに使うようです（海外の本にはよくありますよね）。
そのため、「@<code>$//lead$」は@<LaTeX>{}での引用を表す「@<code>$quotation$」環境に変換されます。

//emlist[サンプル]{
@<letitgo>$//$lead{
土に根を下ろし　風と共に生きよう

種と共に冬を越え　鳥と共に春を歌おう
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//lead{
土に根を下ろし　風と共に生きよう

種と共に冬を越え　鳥と共に春を歌おう
//}

//resultend




=== 図が次のページに送られるときにスペースを空けない

Re:VIEWのデフォルトでは、図を入れるときに現在位置に入りきれない場合は、次のページに送られます。
それは仕方ないのですが、このとき現在位置に大きな空きができてしまいます（@<img>{figure_heretop}の上）。

//image[figure_heretop][図が次のページに送られると、そこに大きな空きができてしまう][scale=0.8]

これに対する解決策として、Starterでは空いたスペースに後続のテキストを流し込む選択肢を用意しています（@<img>{figure_heretop}の下）。

そのためには、Starterのプロジェクト作成ページに「画像が現在位置に入りきらず次のページに回されるとき、大きなスペースを空けない （かわりに後続のテキストを流し込む）」というチェックボックスがあるので、これを選んでください。
または、@<em>{sty/starter.sty}で「@<code>$\renewenvironment{reviewimage}[1][H]$」という箇所を探し、「@<code>$[H]$」を「@<code>$[h]$」に変更してください。

またStarterでは「@<code>$//image$」コマンドを拡張し、図の挿入位置が指定できるようになっています@<fn>{u5dnl}。
これを指定することで、空いたスペースに後続のテキストを流し込むかどうかを、画像ごとに制御できます。
//footnote[u5dnl][実装方法は@<em>{lib/hooks/monkeypatch.rb}を見てください。]

 * 「@<code>$//image[][][$@<strong>$pos=H$@<code>$]$」なら後続のテキストを流し込まない@<br>{}
   （つまり画像を現在位置に強制的に配置する）
 * 「@<code>$//image[][][$@<strong>$pos=h$@<code>$]$」なら後続のテキストを流し込む@<br>{}
   （つまり画像が現在位置に入りきらなければ次のページの先頭に配置する）

画像の倍率も指定する場合は、「@<code>$//image[][][scale=0.5,pos=H]$」のように指定してください。


//note[ページ下部にも画像を配置する]{

「@<code>$pos=H$」や「@<code>$pos=h$」のどちらを選んでも、入りきらない画像は次ページに送られます。
そのため、どうしても画像はページ上部に配置されることが多くなり、逆にページ下部には配置されにくくなります。

このバランスの悪さが気になる場合は、（小さい画像を除いて大きめの画像に）「@<code>$pos=bt$」を指定してみてください。
ここで「@<code>$b$」はボトム(bottom)、「@<code>$t$」はトップ(top)を表します。
つまり、まずページ下部に配置を試み、入らないなら次ページ上部に配置します。
これで、全体的に図がページの上部と下部の両方に配置されるはずです。

//}

//note[「次の図」や「以下の図」という表現を止める]{

すでに説明したように、画像の配置場所として「@<code>$pos=H$」@<strong>$以外$を指定した場合は、後続のテキストが現在位置に流し込まれます。
そのため、文章中で「次の図は〜」とか「以下の図では〜」と書いていると、図が次ページに配置された場合、読者が混乱します。

このような事態を避けるために、「次の図は〜」や「以下の図では〜」という表現を止めて、「図1.1では〜」のように番号で参照するようにしましょう。
面倒でしょうが、仕方がありません。慣れてください。

//}


=== 図のまわりを線で囲む

Starterでは、図のまわりをグレーの線で囲むことができます。
そのためには「@<code>{//image}」の第3引数に「@<code>{border=on}」を指定します。

//emlist[サンプル]{
@<letitgo>$//$image[tw-icon][デフォルトの表示][scale=0.5,pos=H]

@<letitgo>$//$image[tw-icon][まわりを線で囲む][scale=0.5,pos=H,@<b>|border=on|]
//}

//noindent
@<em>{表示結果：}

//resultbegin

//image[tw-icon][デフォルトの表示][scale=0.5,pos=H]

//image[tw-icon][まわりを線で囲む][scale=0.5,pos=H,border=on]

//resultend




=== 何もしない命令「@<code>$@$<letitgo>{...}」

Re:VIEWでは、「@<code>$//list{$ ... @<code>$//}$」や「@<code>$//emlist{$ ... @<code>$//}$」のようなブロック命令の中で、「@<code>$@<b>{$...@<code>$}$」などのインライン命令が利用できます。
そのため、「@<code>$//emlist{$ ... @<code>$//}$」の中で「@<code>$@<b>{$...@<code>$}$」そのものを表示させるには次のようなトリックが必要です。

//emlist[サンプル]{
@<letitgo>$//$emlist{
  @<letitgo>$@$<b>{ABC}
  @<letitgo>$@$<code>$@$<b>{ABC}
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//emlist{
  @<b>{ABC}
  @<code>$@$<b>{ABC}
//}

//resultend



つまり「@<code>$@<b>{$...@<code>$}$」のうち「@<code>$@$」だけを「@<code>$@<code>{$...@<code>$}$」で囲うわけです。

この方法はうまく動作しますが、そもそもソースコードを表示するための「@<code>$//emlist{$ ... @<code>$//}$」の中で「@<code>$@<code>{$...@<code>$}$」を使うのもおかしな話です。

そこでStarterでは、何もしないインライン命令「@<code>$@<letitgo>{$...@<code>$}$」を用意しました。
これを使うと、引数を何も加工せず表示します。

サンプルを見てみましょう。

//emlist[サンプル]{
@<letitgo>$//$emlist{
1. @<letitgo>$@$<b>{ABC}
2. @<letitgo>$@$<letitgo>$@<letitgo>$@$<b>{ABC}$
3. @<letitgo>$@$<letitgo>$@$<b>{ABC}
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//emlist{
1. @<b>{ABC}
2. @<letitgo>$@<b>{ABC}$
3. @<letitgo>$@$<b>{ABC}
//}

//resultend



1番目は、「@<code>$ABC$」が太字で表示されてしまいます。
今は「@<code>$@<b>{ABC}$」と表示したいので、これは意図とは違います。

2番目は、「@<code>$@<b>ABC$」と表示されました（波カッコの「@<code>${$」と「@<code>$}$」が消えています）。
実は@<LaTeX>{}に変換された段階では「@<code>$@<b>{ABC}$」となっていますが、@<LaTeX>{}では波カッコが特別な意味を持つため、「@<code>$@<b>{ABC}$」ではなく「@<code>$@<b>ABC$」と表示されてしまいます。

3番目は、「@<code>$@<b>{ABC}$」と表示されました。
これが期待した出力です。
2番目との違いは、「@<code>$@$@<code>{<letitgo>$}...@<code>{$}」の引数に「@<code>${$」と「@<code>$}$」を含めなかったことです。
これによって、@<LaTeX>{}へ変換するときに「@<code>${$」と「@<code>$}$」が適切にエスケープされます。

このような落とし穴はありますが、ブロック命令の中でインライン命令そのものを表示したい場合は、「@<code>$@<letitgo>{$...@<code>$}$」を使ってください。

なお「@<code>$@<letitgo>{$...@<code>$}$」は長すぎるという意見があったので、エイリアスとして「@<code>$@<nop>{$...@<code>$}$」を用意しました（「nop」は「No Operation」の略です）。


=== 章や項を参照する「@<code>$@$@<code>$<secref>{}$」

Re:VIEWでは、「@<code>$@$@<code>$<hd>{}$」を使って節(Section)や項(Subsection)を参照できます。
しかしこの機能には問題点があります。

 * Re:VIEWのデフォルト設定@<fn>{26mo5}では、章(Chapter)と節(Section)には番号がつくけど、項(Subsection)には番号がつかない。
 * そのため、「@<em>$@<hd>{}$」で項(Subsection)を参照すると、番号がなくて項タイトルだけになるので文章がとても不自然になる。
//footnote[26mo5][Re:VIEWのデフォルトでは@<em>{config.yml}で「@<code>$secnolevel: 2$」と設定されています。これが3以上でないと、項(Subsection)に番号がつきません。]

サンプルを使って説明しましょう。
たとえば次のような原稿ファイルがあったとします。

//emlist[ファイル：chap-pattern.re]{
@<letitgo>$=$ デザインパターンの紹介

@<letitgo>$==${sec-visitor} Visitorパターン

@<letitgo>$===${subsec-motivation} 動機

@<letitgo>$===${subsec-structure} 構造

@<letitgo>$===${subsec-impl} 実装例

//}

文章の構造は次のようになっていますね。

 * 「デザインパターンの紹介」は章(Chapter)
 ** 「Visitorパターン」は節(Section)
 *** 「動機」と「構造」と「実装例」は項(Subsection)

さてRe:VIEWのデフォルト設定のままだと、次のように章と節には番号がつくけど、項には番号がつきません。

//blankline
//noindent
@<em>{表示例：}

//resultbegin

//blankline
//embed[latex]{
\par\noindent
{\LARGE\headfont 第1章　デザインパターンの紹介}
\bigskip
\par\noindent
{\Large\headfont 1.1　Visitorパターン}
\bigskip
\par\noindent
{\large\headfont 動機}
\bigskip
\par\noindent
{\large\headfont  構造}
\bigskip
\par\noindent
{\large\headfont  実装例}
\par
//}
//blankline

//resultend

このことを踏まえたうえで、節や項を「@<code>$@$@<code>$<hd>{}$」で参照するとどう表示されるでしょうか。

 * 節(Section)には番号がついているので、たとえば「@<code>$@$@<code>$<hd>{sec-visitor}$」のように節を参照すると、「1.1 Visitorパターン」のように表示されます。
   これだと番号がついているので、読者は節を探しやすいです。
 * しかし項(Subsection)には番号がついていないので、たとえば「@<code>$@$@<code>$<hd>{subsec-motivation}$」や「@<code>$@$@<code>$<hd>{subsec-structure}$」のように項を参照すると、「動機」や「構造」とだけ表示されてしまいます。
   これだと番号がついていないので、読者は項を探せないでしょう。

//emlist[サンプル（最初の1つは節を参照、残り3つは項を参照）]{
 * @<letitgo>$@$<hd>{sec-visitor}
 * @<letitgo>$@$<hd>{subsec-motivation}
 * @<letitgo>$@$<hd>{subsec-structure}
 * @<letitgo>$@$<hd>{subsec-impl}
//}

//noindent
@<em>{表示結果：}

//resultbegin

 * 「1.1 Visitorパターン」
 * 「動機」
 * 「構造」
 * 「実装例」

//resultend

問題点をもう一度整理しましょう。

 * Re:VIEWのデフォルト設定では、項(Subsection)に番号がつかない。
 * そのため、「@<code>$@$@<code>$<hd>{}$」で項を参照するとタイトルだけになってしまい、番号がつかないので読者が項を探せない。

この問題に対し、Starterでは「@<code>$@$@<code>$<secref>{}$」という新しい命令を用意しました。
この新命令には次のような利点があります。

 * 番号のついていない項でも、親となる節を使うことで探しやすい表示をしてくれる。
 * その項のページ番号がつくので、該当ページに直接アクセスできる。

次のサンプルを見れば、「@<code>$@$@<code>$<hd>{}$」との違いがすぐに分かるでしょう。

//emlist[サンプル（最初の1つは節を参照、残り3つは項を参照）]{
 * @<b>$@$@<b>$<secref>${sec-visitor}
 * @<b>$@$@<b>$<secref>${subsec-motivation}
 * @<b>$@$@<b>$<secref>${subsec-structure}
 * @<b>$@$@<b>$<secref>${subsec-impl}
//}

//noindent
@<em>{表示結果：}

//resultbegin

 * 「1.1 Visitorパターン」(p.1)
 * 「1.1 Visitorパターン」内の「動機」(p.1)
 * 「1.1 Visitorパターン」内の「構造」(p.1)
 * 「1.1 Visitorパターン」内の「実装例」(p.1)

//resultend

これを見ると、番号がついていない項の前に番号がついている節が置かれていること、またページ番号がついていることが分かります。
どちらも@<code>$@$@<code>$<hd>{}$にはない特徴であり、@<code>$@$@<code>$<hd>{}$で参照するより節や項が探しやすくなります。

その他の注意事項です。

 * 「@<code>$@$@<code>$<secref>{}$」は、節でも項でも、あるいは目(Subsubsection)でも参照できます。
   今まで「@<code>$@$@<code>$<hd>{}$」を使っていた箇所はすべて「@<code>$@$@<code>$<secref>{}$」で置き換えられます。
   ただし、章(Chapter)は参照できないので、その場合は「@<code>$@$@<code>$<chapref>{}$」を使ってください。
 * 項にも番号をつけるよう設定している場合は、「@<code>$@$@<code>$<secref>{}$」の表示結果は「@<code>$@$@<code>$<hd>{}$」にページ番号をつけたものと同じです。
 * 他の章(Chapter)の節や項を参照する場合は、たとえば@<br>{}
  「@<code>$@$@<code>$<secref>{chap-pattern|sec-visitor}$」や@<br>{}
  「@<code>$@$@<code>$<secref>{chap-pattern|subsec-impl}$」のように書いてください。わざわざ@<br>{}
  「@<code>$@$@<code>$<secref>{chap-pattern|sec-visitor|subsec-impl}$」のように書く必要はありません。


=== 「@<em>$@$@<em>$<chapref>{}$」や「@<em>$@$@<em>$<hd>{}$」をリンクに

Starterでは、「@<letitgo>$@$<chapref>{}」や「@<letitgo>$@$<hd>{}」がリンクになるように設定しています。
そのために次のような設定をしています。

 * @<em>{config.yml}に「@<code>$chapterlink: true$」という設定を追加（最終行）。
 * @<em>{sty/starter.sty}で「@<em>{\reviewsecref}」を再定義し、「@<em>{\hyperref}」を使うように変更。

//emlist[リスト：\reviewsecrefを再定義]{
\renewcommand{\reviewsecref}[2]{%
  \hyperref[#2]{#1}(p.\pageref{#2})%     % 節や項のタイトルがリンク
  %{#1}(\hyperref[#2]{p.\pageref{#2}})%  % ページ番号がリンク
}
//}

これらはRe:VIEWに実装済みの機能であり、Starterはそれらを有効化しただけです。
しかしこれらの機能はRe:VIEWのドキュメントには書かれていないので、もしかしたら将来的に変更されるかもしれません。

またStarterの追加機能である「@<em>{@}@<em>$<secref>{}$」でも、リンクが作成されます。


=== ターミナルでのカーソル

ターミナルでのカーソルを表す機能を用意しました。
たとえば次の例では、2行目の真ん中の「@<code>{f}」にカーソルがあることを表しています。

//terminal[][カーソル]{
function fib(n) {
  return n <= 1 ? n : @<cursor>{f}ib(n-1) : fib(n-2);
}
~
~
"fib.js" 3L, 74C written
//}


=== その他

 * ブロック命令「@<code>$//clearpage$」で改ページします。
   また過去との互換性のために、インライン命令「@<code>$@<clearpage>{}$」も使えます。
 * 「@<code>$@<hearts>{}$」とすると、「@<hearts>{}」と表示されます。
 * 「@<code>$@<TeX>{}$」とすると、「@<TeX>{}」と表示されます。
 * 「@<code>$@<LaTeX>{}$」とすると、「@<LaTeX>{}」と表示されます。



=={sec-design} レイアウトやデザインに関する変更や拡張

=== フォントサイズの変更に対応

Re:VIEW 2.5は、標準では本文のフォントサイズを9ptや8ptに指定しても、効いてくれません（まじかー！）。
ウソだと思うかも知れませんが、実際に苦しんだ人の証言@<fn>{g6rdf}があるのでご覧ください。
先人の苦労が偲ばれます。
//footnote[g6rdf][@<href>{https://www.slideshare.net/KazutoshiKashimoto/nagoya0927-release}のp.21とp.22。]

//image[slide2][フォントやページサイズを変更できなかった人の証言]

この問題は、「@<em>{geometry.sty}」というスタイルファイルをオプションなしで読み込んでいることが原因です@<fn>{ly58b}。
Starterではこれを読み込まないように修正している@<fn>{z4ccg}ため、フォントサイズを9ptや8ptに指定すればそのサイズになります。
//footnote[ly58b][簡単に書いてますけど、原因が@<em>{geometry.sty}であることを突き止めるのには大変な時間がかかり、正月休みを潰してしまいました。コノウラミハラサデオクベキカ！]
//footnote[z4ccg][修正箇所は、@<em>{layouts/layout.tex.erb}の50行目あたりです。]

=== A5サイズの指定に対応
Re:VIEW 2.5は、標準ではA5サイズの指定が効いてくれません（まじかー！）。
ウソだと思うかも知れませんが、実際にトラブルに陥った人の証言があります@<fn>{m10ye}。
//footnote[m10ye][@<href>{https://blog.vtryo.me/entry/submit-of-journey}]

//quote{
　@<br>{}
@<strong>{トラブル発生！！}@<br>{}@<br>{}
原稿データチェック、表紙チェック、ともに問題なく終わったかにみえた午後1時。@<br>{}
何かに気づいたお姉さんの声音が変わりました。@<br>{}
「すみません、PDFサイズ……B5になってます」@<br>{}
「えっ……」@<br>{}
めのまえがまっくらになった。@<br>{}
セイチョウ・ジャーニーはA5で制作しているはずなのに、B5サイズに？？@<br>{}
わからない！どうして！だって何度も確認したはずだ！！@<br>{}
と度重なる徹夜で脳死寸前の僕はパニック状態になりました。@<br>{}
//}

入稿で明らかになるトラブル！怖いですねー。
こういう予期せぬトラブルがあるので、締切りギリギリまで作業するのは止めて、余裕をもって入稿しましょう。

さて、A5にならない問題は2種類あります。

 * 本文の大きさがA5サイズにならない。
 * 本文の大きさはA5なのにPDFがA5サイズにならない。

前者は、「@<em>{geometry.sty}」が原因です。
すでに説明したように、Starterでは「@<em>{geometry.sty}」を読み込まないようにしているため、この問題は起こりません。

後者は、上で紹介したトラブルですね。
これは@<em>{jsbook.sty}のオプションに「@<em>{papersize}」が指定されてないせいです。
Starterではこのオプションを指定しているので、A5やB5の指定どおりのPDFが生成されます。

詳しくは、@<em>{config.yml}の「@<code>$texdocumentclass:$」を参照してください。

//emlist[config.yml]{
texdocumentclass: ["jsbook",
    #"uplatex,papersize,twoside,b5j,10pt,openright" # B5 10pt 右起こし
    #"uplatex,papersize,twoside,b5j,10pt,openany"   # B5 10pt 両起こし
    #"uplatex,papersize,twoside,a5j,9pt,openright"  # A5  9pt 右起こし
    #"uplatex,papersize,twoside,a5j,9pt,openany"    # A5  9pt 両起こし
    #"uplatex,papersize,oneside,a5j,10pt,openany"   # A5 10pt 両起こし
    "uplatex,papersize,twoside,a5j,9pt,openright"
]
//}


=== 本文の幅を全角40文字より長くできる

@<LaTeX>{}の@<em>{jsbook.cls}ファイルを使うと、デフォルトでは本文の幅の最大値が40文字までに制限されています。
これは、1行が全角40文字より長いと読みづらくなるからという理由だそうです@<fn>{b1flb}。
//footnote[b1flb][@<href>{https://oku.edu.mie-u.ac.jp/~okumura/jsclasses/}に、@<em>{jsbook.cls}の作者である奥村先生が『書籍では1行の長さが全角40文字を超えないようにしています。』と解説しています。]

そのため、B5サイズだとページ左右の余白が広めになってしまいます。
ページ数を抑えて印刷代を下げたい人にとって、この余白はコストを増加させる要因です。

Starterでは@<em>{sty/mytextsize.sty}で本文幅を再設定することで、本文の幅を40文字より広くできます。
B5サイズでフォントが10ptだと、1行あたり全角42〜45文字がいいでしょう。

ただしA5サイズ（フォント9pt）では、1行あたり40文字を超えるのはやめたほうがいいです。
参考までに市販の技術書だと、A5サイズで1行あたり全角39文字にすることが多いようです。


=== 奇数ページと偶数ページで左右の余白を変える

本文の幅を広げる場合でも、左右の余白はちゃんと取りましょう。

 * 本を開いたときの中央（「ノド」という）の余白、つまり左ページの右余白と右ページの左余白は、最低でも2cmは確保しましょう。
   そうしないと、ノド近くの文章がとても読みづらくなります。
 * 本を開いたときの外側（「小口」という）の余白、つまり左ページの左余白と右ページの右余白は、最低でも1cmは確保しましょう。
   そうしないと、ページをめくるときに指が本文にかかってしまい、読みにくいです。

Starterではこういったことを考慮し、本文の幅を広げる（つまり1行あたりの文字数を増やす）場合には小口側の余白だけを減らすようにしています。
詳しくは@<em>{sty/mytextsize.sty}を見てください。


=== ページ上部の余白を減らし、その分を本文の高さに追加

@<LaTeX>{}の標準のデザインでは、ページ上部の余白が大きめになっています。
ページ数を少しでも減らして印刷代を抑えたい場合は、この余白がとても気になります。

Starterではこの余白を約1cm減らし@<fn>{g2ohz}、その分を本文の高さに追加しています。
詳しくは@<em>{sty/mytextsize.sty}を見てください。
//footnote[g2ohz][実はjsbook.clsでは「@<em>{1cm}」は1cmより少し大きく扱われ、厳密に1cmを指定したい場合は「@<em>{1truecm}」とする必要があります。しかしここではそこまで厳密な1cmを必要とはしていないので、@<em>{sty/mytextsize.sty}では「@<em>{1cm}」と指定しています。]


=== ソースコード表示用のフォントを変更

@<LaTeX>{}のデフォルトでは、装飾が多めのフォントがソースコードの表示に使われています（@<img>{font_beramono}の上半分）。
このフォントは「0」と「O」や「1」と「l」の区別がつきにくく、また太字にしてもあまり目立たないという欠点があります。

//image[font_beramono][ソースコードの表示に使われるフォント][scale=0.7]

Starterでは、ソースコードの表示に使うフォントを、装飾が少ないもの（Bera Mono@<fn>{62vxj}）に変更しています（@<img>{font_beramono}の下半分）。
このフォントは「0」と「O」や「1」と「l」の区別がつきやすく、また太字にしたときも目立つようになっています。
ただし「@<code>$'$」（シングルクォート）と「@<code>$`$」（バッククォート）の区別がつきにくくなっているので注意してください。
//footnote[62vxj][@<href>{http://www.tug.dk/FontCatalogue/beramono/} でサンプルが見れます。]

ソースコードの表示に向くフォントとしては、他にも「Inconsolata」@<fn>{iii4v}や「Nimbus Mono Narrow」@<fn>{vo5f3}があります。
興味がある人は調べてみてください。
//footnote[iii4v][@<href>{http://www.tug.dk/FontCatalogue/inconsolata/} でサンプルが見れます。]
//footnote[vo5f3][@<href>{http://www.tug.dk/FontCatalogue/nimbus15mononarrow/} でサンプルが見れます。]


=== 章や節のデザインを変更可能

Starterでは、章(Chapter)や節(Section)のデザインを変更できます。
例を2つ挙げておきます（@<img>{chaphead_design_3}、@<img>{chaphead_design_2}）。

//image[chaphead_design_3][章タイトルをセンタリング、上下に太線、節タイトルに下線][scale=0.7]

//image[chaphead_design_2][章タイトルを右寄せ、下に細線、節タイトルの行頭にクローバー][scale=0.7]

これらのデザインを調整するときは、@<em>{sty/starter.sty}を編集してください。

なおStarterでは、@<img>{chaphead_design_3}のように章タイトルの上下に太い線を入れた場合でも、まえがきや目次やあとがきのタイトルには太い線を入れないようにしています。
これは意図的な仕様です。


=== 章のタイトルページを作成可能

Starterでは、章(Chapter)のタイトルと概要を独立したページにできます（@<img>{chaptitlepage_sample}）。
これは商用の書籍ではよく見かける方法です。

//image[chaptitlepage_sample][章のタイトルと概要を独立したページにした例（章ごとの目次つき）][scale=0.5]

やり方は簡単で、章タイトルと概要を書いたあとに「@<code>$//makechaptitlepage[toc=section]$」と書くだけです。
これで章タイトルページが作られ、背景色がつき、その章の目次もつきます@<fn>{8poyo}。
//footnote[8poyo][実装の詳細は@<em>{sty/starter.sty}の@<em>{makechaptitlepage}コマンドを参照してください。]

//emlist[サンプル]{
= Re:VIEW Starter FAQ

@<letitgo>$//$abstract{
残念ながら、Re:VIEWでできないことは、Starterでもたいていできません。

このFAQでは、「何ができないか？」を中心に解説します。
@<letitgo>$//$}

@<b>$//makechaptitlepage[toc=section]$
//}

ただし、「@<code>$//makechaptitlepage[toc=section]$」はすべての章に書く必要があります。
これを書き忘れた章があると、そこだけ章タイトルページが作られません。
注意してください。


=== 目次の文字を小さく、行間を狭く

Starterでは、目次のデザインを少し変更しています。

 * 章(Section)の文字をゴシック体にしました。
   項(Subsection)の文字は明朝体のままなので、これで目次での章と項が見分けやすくなります。
 * 項(Subsection)の文字を少し小さくし、行間を狭くしました。
   これにより、目次にとられるページ数を少しだけ減らせます。

目次のデザインを修正する場合は、@<em>{sty/starter.sty}の中で「@<em>{\l@section}」や「@<em>{\l@subsection}」を探して、適宜修正してください。
特に目次のページ数が多い場合は、行間を狭めて（「@<em>{\baselineskip}」を小さくして）みてください。


=== キャプションのデザインを変更

Starterでは、ソースコードや表や図のキャプション（説明）を次のように変更しています。

 * フォントをゴシック体にする
 * 先頭に「▲」や「▼」をつける

これはTechBooster製テンプレートのデザインを参考にしました。
ただし@<LaTeX>{}マクロの定義はまったく別です@<fn>{82e4v}。

//footnote[82e4v][なおこれに関して、「@<code>$\reviewimagecaption$」というコマンドを新たに定義し、「@<code>$\reviewimage$」環境が「@<code>$\caption$」のかわりにそれを使うよう、LATEXBuilder#image_image()にモンキーパッチを適用しています。モンキーパッチはlib/hooks/monkeypatch.rbにあり、review-ext.rbが読み込んでいます。]


=== 引用のデザインを変更

引用「@<code>$//quote{$ ... @<code>$//}$」のデザインを変更し、左側に縦棒がつくようにしました。

Re:VIEWでは@<LaTeX>{}のデフォルトデザインのまま（全体が少しインデントされるだけ）なので、引用であることが分かりにくいです。
これに対し、Starterでは左側に縦棒がつくので、引用であることがより分かりやすくなっています。

また引用中に複数の段落を入れた場合、段落の先頭が1文字分インデントされます（Re:VIEW標準ではインデントされません）。

//emlist[サンプル]{
@<letitgo>$//$quote{
その者蒼き衣を纏いて金色の野に降りたつべし。
失われし大地との絆を結び、ついに人々を清浄の地に導かん。
@<letitgo>$//$}
//}

//noindent
@<em>{表示結果：}

//resultbegin

//quote{
その者蒼き衣を纏いて金色の野に降りたつべし。
失われし大地との絆を結び、ついに人々を清浄の地に導かん。
//}

//resultend




=== ページヘッダーを変更

一般の書籍では、ページヘッダーは次のような形式になっています。

 * 見開きで左のページのヘッダーには、章タイトルを表示
 * 見開きで右のページのヘッダーには、節タイトルを表示

しかしRe:VIEWでは、両方のページのヘッダーに章タイトルと節タイトルが表示されています。
これはおそらく、タブレットのような見開きがない閲覧環境を想定しているのだと思います。

Starterではこれを変更し、一般の書籍と同じようなヘッダーにしています。
ただしタブレット向けの場合は、Re:VIEWと同じようにしています。


=== ページ番号のデザインを変更

Re:VIEWのデフォルトでは、ページ番号はたとえば「10」のように表示されるだけです。

Starterでは、ページ番号を「@<embed>$--$ 10 @<embed>$--$」のような表示に変更しています。
これは、ページ番号であることをより分かりやすくするためです。
詳しくは@<em>{sty/starter.sty}を参照してください。


=== 箇条書きの行頭記号を変更

@<LaTeX>{}では、箇条書きの行頭に使われる記号が、第1レベルでは小さい黒丸「@<embed>{|latex|$\bullet$}」、第2レベルではハイフン「@<embed>{|latex|--}」でした。

//blankline
//noindent
@<em>{表示結果（変更前）：}

//embed[latex]{
{\renewcommand{\labelitemii}{--}
//}

 * 第1レベル
 ** 第2レベル

//embed[latex]{
}
//}

しかしこれだと、箇条書きの記号ではなくマイナス記号に見えてしまいます。

Starterではこの第2レベルの記号を、小さい白丸「@<embed>{|latex|$\circ$}」に変更しました。
これで、より自然な箇条書きになりました。

//blankline
//noindent
@<em>{表示結果（変更後）：}

 * 第1レベル
 ** 第2レベル


=== タイトルページと奥付を独立したファイルに

Starterでは、タイトルページ（「大扉」といいます）と、本の最終ページにある「奥付」を、それぞれ別ファイルに分離しました。

 * @<em>{sty/mytitlepage.sty} … タイトルページを表します。
 * @<em>{sty/mycolophon.sty} … 奥付を表します。

タイトルページや奥付のデザインが気に入らない場合は、これらを編集してください。


=== 奥付が必ず最終ページになるよう修正

Re:VIEWでは、奥付のページは単に改ページされてから作成されます。
そのため、場合によっては奥付がいちばん最後のページではなく、最後から2番目のページになることがあります（この場合、最後のページは空白ページになります）。

Starterではこれを改善し、奥付が必ず最後のページになるようにしています。
詳しくは@<em>{sty/mycolophon.sty}の「@<code>$\clearpage\pltx@cleartoleftpage$」という箇所、または@<em>{sty/starter.sty}の「@<code>$\reviewcolophon$」コマンドを参照してください。


=== コラムがページまたぎする場合は横線を入れない

Starterでは、コラムが長くてページをまたいでしまう場合に、横線をいれないようにしています（@<img>{column_openframe}）。
こうすると、コラムが続いていることが分かりやすいです。

//image[column_openframe][コラムがページをまたぐときに横線を入れない][scale=0.8]



=={sec-sty} @<LaTeX>{}のコマンドやスタイルファイルに関する機能

=== スタイルシートを追加

Starterでは、次のような独自のスタイルファイルを追加しています。

 : config-starter.yml
	Starterでプロジェクトを作成したときに選んだオプション（の一部）が書かれたファイルです。
	ここに書かれているオプションは、プロジェクトをダウンロードしたあとからでも変更できます。
 : sty/starter.sty
	Starterのサイトで選択したオプションに従って生成されたスタイルファイルです（Starterのバージョンが上がるたび、このファイルもよく変更されます）。
	デザインを調整したい場合などはこのファイルを編集するか、後述の@<em>{sty/mystyle.sty}で上書きしてください。
 : sty/mytextsize.sty
	本文の幅やページ左右の余白を設定するためのスタイルファイルです。
	PDFのサイズ（B5やA5）を変更する場合は、@<em>{config.yml}の「@<code>$texdocumentclass:$」を変更してください。
 : sty/mystyle.sty
	ユーザ独自の@<LaTeX>{}マクロ（コマンドや環境）を追加したり、既存のマクロを上書きするためのファイルです。
	中身は空なので、自由に追加や上書きしてください。
 : sty/mytitlepage.sty
	タイトルページ（大扉）の内容を表すスタイルファイルです。
	デザインが気に入らない場合は編集してください。
 : sty/mycolophon.sty
	最終ページの「奥付」を表すスタイルファイルです。
	デザインが気に入らない場合は編集してください。

@<em>{sty/mytextsize.sty}と@<em>{sty/starter.sty}は、どちらも自動生成されます。
なので同じファイルにできそうですが、読み込むタイミングが異なるため、別ファイルにしています。

 * @<em>{sty/mytextsize.sty}は本文の幅や高さを指定するので、他のスタイルファイルより先に読み込まれます。
 * @<em>{sty/starter.sty}は既存の@<LaTeX>{}マクロ（コマンドや環境）を上書きするので、他のスタイルファイルより後に読み込まれます。


==={bn2iw} 印刷用PDFと電子用PDFを切り替える

Starterには、印刷用PDFと電子用PDFを切り替えて出力する機能があります@<fn>{ctr1x}。
//footnote[ctr1x][ただしタブレット用にプロジェクトを作成した場合は、切り替えは無意味です。]

 : 印刷用PDF
	紙に印刷するためのPDFです。色はモノクロで、またA5の場合はページ左右の余白幅を変更します。
 : 電子用PDF
	ダウンロードで配布するためのPDFです。色はカラーで、ページ左右の余白は同じ幅です。

//note[ページ左右の余白幅を変える理由]{

印刷用PDFにおいてページ左右の余白幅を変更するのは、本の読みやすさを保ったまま1行あたりの文字数を増やすためです。B5の場合はたいてい十分な紙幅があるので、ページ左右の余白幅は同じままで大丈夫です。A5の場合は見開きで内側の余白幅を確保したまま、外側の余白幅を狭めることで、1行あたりの文字数を増やします。

//image[margin_book][ページ左右の余白幅を変更する理由][scale=0.75,pos=H]

当然ですが、このような変更は電子用PDFでは必要ありません。
//}

設定ファイル@<code>{config-starter.yml}の中にある「@<code>{starter: target: }@<i>{xxx}」の値が「@<code>{pbook}@<fn>{0mxlb}」だと印刷用PDFが、「@<code>{ebook}@<fn>{4545b}」だと電子用PDFが生成されます。初期設定では「@<code>{pbook}」になっているので、デフォルトでは印刷用PDFが生成されます。
//footnote[0mxlb][「pbook」はprinting bookの略です。]
//footnote[4545b][「ebook」はelectric bookの略です。]

またこの値は環境変数@<fn>{4r53n}@<code>{$STARTER_TARGET}で上書きできます。具体的には次のようにすると印刷用と電子用のPDFを切り替えられます。
//footnote[4r53n][環境変数とは、コマンドプロセスが参照する外部変数です。環境変数を設定することでコマンドの挙動を一部変更できます。詳しくは「環境変数」でぐぐってください。]

//terminal[][印刷用PDFと電子用PDFを切り替える]{
### 印刷用PDFを生成（デフォルト）
$ rake pdf    # または STARTER_TARGET=pbook rake pdf

### 電子用PDFを生成（環境変数を使って設定を上書き）
$ STARTER_TARGET=ebook rake pdf
//}

ただしこの機能では、@<LaTeX>{}のスタイルファイル（@<code>{sty/starter.sty}や@<code>{sty/mytextsize.sty}）の中で行える範囲でしか変更はできません。それ以上のことがしたい場合は、@<secref>{chap02-faq|qvtlq}を参照してください。


=== コンパイル時の出力を抑制

@<LaTeX>{}でコンパイルすると（つまり@<em>{uplatex}コマンドを実行すると）、通常ではたくさんのメッセージが出力されます。
これはとてもうざいので、Starterでは出力を抑制するために@<em>{uplatex}コマンドに「@<code>{-interaction=batchmode}」オプションをつけています。

しかしこのオプションをつけると、今度はエラーメッセージが表示されないという問題があります。
つまり、こういうことです：

 * 出力を抑制したいなら、@<LaTeX>{}コマンドに「@<code>{-interaction=batchmode}」オプションをつける。
 * しかし「@<code>{-interaction=batchmode}」オプションをつけると、エラーメッセージが表示されない。

なんというクソ仕様でしょう！
このクソ仕様を、Starterでは次のように回避しています。

 1. 「@<code>{-interaction=batchmode}」オプションをつけてコンパイルする。
 2. エラーになったら（つまりコマンドの終了ステータスが0でなければ）、「@<code>{-interaction=batchmode}」オプションを@<strong>{つけずに}コンパイルし直すことで、エラーメッセージを表示する。

今のところ、この方法がいちばん妥当でしょう。

なおこの変更は「@<em>{rake pdf}」コマンドでのみ行われます@<fn>{g6wy6}。
「@<em>{review-pdfmaker config.yml}」を実行した場合はもとの挙動（つまりコンパイルメッセージがたくさん出る）になるので注意してください。
//footnote[g6wy6][実装の詳細は@<em>{lib/tasks/review.rake}を参照してください。]

ちなみに、@<LaTeX>{}のコマンドはエラーメッセージを標準エラー出力(stderr)に出してくれません。
クソかよ。


=== @<LaTeX>{}コマンドにオプションを追加

Starterでは、@<LaTeX>{}コマンド（@<em>{uplatex}）に以下のオプションをつけています。

: @<code>{-halt-on-error}
	@<LaTeX>{}のコンパイルエラー時に、インタラクティブモードにせず、そのままコマンドを終了させるオプションです。
: @<code>{-file-line-error}
	@<LaTeX>{}のコンパイルエラー時に、エラー発生箇所の行番号に加えて、ファイル名も出力するようにするオプションです。

指定箇所は@<em>{config.yml}の「@<code>$texoptions:$」です。


=== 実行する@<LaTeX>{}コマンドをオプションつきで出力

Starterでは、実行する@<LaTeX>{}コマンドをオプションつきで出力するように変更しています@<fn>{7a93y}。
こうすることで、特にエラーが発生した場合にどんなコマンドを実行したかを調べるのに役立ちます。
//footnote[7a93y][この変更は、@<em>{lib/tasks/review.rake}で定義されている「@<code>{pdf}」タスクを書き換えることで実現しています。]

ただしこれは「@<code>{rake pdf}」を実行したときだけであり、コマンドラインから直接「@<code>{review-pdfmaker config.yml}」を実行したときは出力されません@<fn>{orc59}ので注意してください。
//footnote[orc59][なぜなら、この変更は「@<code>{pdf}」タスクを書き換えることで実現しているので、@<em>{review-pdfmaker}コマンドには影響しないからです。]

次が実行例です。
@<em>{uplatex}コマンドや@<em>{dvipdfmx}コマンドが、オプションつきで出力されていることが分かります。

//terminal[][実行例]{
$ rake pdf
compiling chap00-preface.tex
compiling chap01-starter.tex
compiling chap02-review.tex
compiling chap99-postscript.tex

[review-pdfmaker]$ /usr/bin/ruby /tmp/xxx-book/lib/hooks/beforetexcompile.rb /tmp/xxx-book/xxx-book-pdf /tmp/xxx-book

[review-pdfmaker]$ uplatex -halt-on-error -file-line-error -interaction=batchmode samplebook.tex
This is e-upTeX, Version 3.14159265-p3.8.1-u1.23-180226-2.6 (utf8.uptex) (TeX Live 2018) (preloaded format=uplatex)
 restricted \write18 enabled.
entering extended mode

[review-pdfmaker]$ uplatex -halt-on-error -file-line-error -interaction=batchmode samplebook.tex
This is e-upTeX, Version 3.14159265-p3.8.1-u1.23-180226-2.6 (utf8.uptex) (TeX Live 2018) (preloaded format=uplatex)
 restricted \write18 enabled.
entering extended mode

[review-pdfmaker]$ uplatex -halt-on-error -file-line-error -interaction=batchmode samplebook.tex
This is e-upTeX, Version 3.14159265-p3.8.1-u1.23-180226-2.6 (utf8.uptex) (TeX Live 2018) (preloaded format=uplatex)
 restricted \write18 enabled.
entering extended mode

[review-pdfmaker]$ dvipdfmx -d 5 -z 3 book.dvi
book.dvi -> book.pdf
[1][2][3][4][5][6][7][8][9][10][11][12]
386603 bytes written
//}

なお実行結果を見ると、@<LaTeX>{}のコンパイル（つまりuplatexコマンドの実行）が3回行われていることが分かります。
これはバグではなく、Re:VIEWの仕様です。
理由は、ページ数に変更があっても対応できるようにするためと思われます。


=== PDF生成を高速化する

DVIファイルをPDFファイルに変換する「@<em>{dvipdfmx}」コマンドのオプションを、圧縮率を少し下げるかわりに短時間で終わるようにするよう、設定しました。

具体的には、@<em>{config.yml}の「@<code>$dvioptions:$」という項目を、Re:VIEWのデフォルトの「@<code>$"-d 5 -z 9"$」から「@<code>$"-d 5 -z 3"$」に変更しています。
「@<code>$-z 9$」は圧縮率を最大にするので時間がかかり、「@<code>$-z 3$」は圧縮率を下げるかわりに短時間で済みます。

PDFファイルのサイズを少しでも減らしたい場合は、「@<code>$-z 9$」にしてみてください。


=== PDFにノンブルをつける

印刷所によっては、PDFにノンブルをつけるのが必須です。
たとえば日光企画@<fn>{lmknh}さんは、ノンブルをつけないと入稿ができません@<fn>{26k16}。
//footnote[lmknh][技術書典でいちばん多くのサークルがお世話になっている印刷所。電話対応のお姉さんがとても親切。入稿ページの使い方が分かりにくいので、ほとんどの初心者はお姉さんのお世話になるはず。]
//footnote[26k16][@<href>{http://www.nikko-pc.com/q&a/yokuaru-shitsumon.html#3-1}より引用：『ノンブルは全ページに必要です。ノンブルが無いものは製本時にページ順に並び替えることが非常に困難な為、落丁・乱丁の原因となります。』]

//note[■ノンブルとは]{

ノンブルとは、すべてのページにつけられた通し番号です。
ページ番号と似ていますが、ページ番号が読者のための番号なのに対し、ノンブルは印刷所の人が間違えずに作業するための番号です。
具体的には次のような違いがあります。

 * ページ番号は読者のためにつけるので、読者から見えやすい場所につける。
   ノンブルは印刷所の人が見えればいいので、読者には見えにくい場所につける。
 * ページ番号は、まえがきや目次では「i, ii, iii, ...」、本文では「1, 2, 3, ...」と増える。
   ノンブルは最初から「1, 2, 3, ...」と増える。
 * ページ番号は、タイトルページや空白ページではつかないことがある。
   ノンブルは、すべてのページに必ずつける必要がある。

詳しくは「ノンブル」でGoogle検索してください。

//}

Starterでは、PDFにノンブルをつけるためのrakeタスク「@<em>{pdf:nombre}」@<fn>{nqjz9}を用意しています。
//footnote[nqjz9][@<em>{lib/tasks/starter.rake}で定義されています。]

//terminal{
$ gem install combine_pdf    # 事前作業（最初の1回だけ）
$ rake pdf:nombre
//}

これで、PDFファイルにノンブルがつきます。

もし@<em>{pdf:nombre}タスクがうまく動作しない場合は、かわりに@<href>{https://kauplan.org/pdfoperation/}を使ってください。


=== rakeコマンドのデフォルトタスクを指定する

Re:VIEWでは、rakeのデフォルトタスクが「@<em>{epub}」になっています。
つまり引数なしでrakeコマンドを実行すると、epubを生成するタスクが実行されます。

これはあまり便利とはいえないし、なによりRubyとrakeをよく知らない人にとっては優しくない仕様です。

そこでStarterでは、rakeの使い方を表示する「@<em>{help}」タスクを用意し、これをデフォルトタスクにしています。
このおかげで、引数なしでrakeコマンドを実行するとrakeの使い方が表示されます。
このほうが、Rubyとrakeをよく知らない人にとって優しいでしょう。

//terminal[][引数なしでrakeコマンドを実行すると、rakeの使い方が表示される][fold=off]{
$ rake
rake -T
rake all            # generate PDF and EPUB file
rake clean          # Remove any temporary products
rake clobber        # Remove any generated files
rake epub           # generate EPUB file
rake help           # + list tasks
rake html           # build html (Usage: rake build re=target.re)
rake html_all       # build all html
rake images         # + convert images (high resolution -> low resolution)
rake images:toggle  # + toggle image directories ('images_{lowres,highres}')
rake pdf            # generate PDF file
rake pdf:nombre     # + add nombre (rake pdf:nombre [file=*.pdf] [out=*.pdf])
rake preproc        # preproc all
rake web            # generate stagic HTML file for web
//}

上の表示結果のうち、コマンドの説明文の先頭に「@<code>{+}」がついているのが、Starterで独自に用意したタスクです。

また環境変数「@<em>{$RAKE_DEFAULT}」を設定すると、それがデフォルトタスクになります。
たとえば「@<em>{pdf}」タスクをデフォルトにしたい場合は、次のようにします。

//terminal[][pdfタスクをデフォルトタスクにする]{
$ export RAKE_DEFAULT=pdf    # デフォルトタスクを変更する。
$ rake                       # 引数がないのにpdfタスクが実行される。
compiling chap00-preface.tex
compiling chap01-starter.tex
compiling chap02-review.tex
compiling chap99-postscript.tex

[review-pdfmaker]$ uplatex -halt-on-error -file-line-error -interaction=batchmode samplebook.tex
....(以下省略)....
//}
