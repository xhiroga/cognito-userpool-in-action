= ユーザー移行の基本

//abstract{
既存のユーザー認証基盤からUserPoolにユーザーを移行する方法は、大まかに2種類用意されています。  
本章では、まずそれぞれのユーザー移行方法について紹介し、次に使い分けについて考えます。
//}

UserPoolが用意しているユーザー移行の方法は、主に2つあります。  
それ以外に、UserPoolのAPIを用いた移行スクリプトの自作も考えられます。しかし、基本的には用意されている方法で十分でしょう。

=={sec-ext} ユーザー移行LambdaトリガーとCSVファイル

=== ユーザー移行Lambdaトリガー
ユーザーがUserPoolに初めてログインした際に、AWS Lambdaがユーザーに代わって移行前のユーザー認証基盤にログインし、取得したログイン情報をUserPoolに渡すやり方です。  
2018年2月から可能になりました。  
ユーザーの認証情報を直接受け取るので、パスワードを移行することが可能です。


=== CSVファイルからのユーザーのインポート
所定の形式のCSVファイルから、UserPoolにユーザーをインポートすることができます。ただし、パスワードだけはインポートすることができません。  
公式ドキュメントにあるとおり、UserPoolではパスワード（のハッシュ）のインポートがサポート外のためです。そのため、CSVファイルからインポートされたユーザーはパスワードリセットを行う必要があります。


=={sec-ext} どちらを利用すべき？

ユーザー移行LambdaトリガーとCSVファイルのインポートのどちらを利用すべきでしょうか。まずは表（@<img>{user_migration_pros_cons}）をご覧ください。@<br>{}
//image[user_migration_pros_cons][ユーザー移行方法ごとのメリット・デメリット][scale=0.8]

最大のポイントはパスワードの移行の可否です。ユーザーにパスワードの変更を案内できるのであれば、CSVファイルによるユーザーのインポートで問題ないでしょう。@<br>{}

シームレスなユーザー移行が必要な場合はユーザー移行Lambdaトリガーを利用することになります。しかし、この方法だといつまでもUserPoolに移行されないユーザーがいるかもしれません。
一定期間はユーザー移行Lambdaトリガーを運用し、大多数のユーザーが移行できたところでCSVファイルのインポートに切り替える、という方法も考えられるでしょう。@<br>{}
