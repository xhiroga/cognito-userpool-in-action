= ユーザー移行の基本

//abstract{
既存のユーザー認証基盤をUserPoolで置き換えるには、ユーザーデータの移行とユーザー認証基盤を参照する処理の修正の2つの対応が必要です。
本章では、まずユーザーデータの移行についてどんな方法があり、どのように選ぶのが良いかを述べます。続いて、ユーザー認証基盤を参照する処理の対応のポイントに触れます。

UserPoolへのユーザー移行にはいくつか方法があります。具体的にどんな方法か、どちらを選ぶべきかについて紹介します。  

//}


=={sec-ext} ユーザー移行の3つの方法

=== CSVファイルからのユーザーのインポート
所定の形式のCSVファイルから、UserPoolにユーザーをインポートすることができます。ただし、パスワードだけはインポートすることができません。  
公式ドキュメントにあるとおり、UserPoolではパスワード（のハッシュ）のインポートがサポート外のためです。そのため、CSVファイルからインポートされたユーザーはパスワードリセットを行う必要があります。

余談ですが、CSVのインポート時の...


=== ユーザー移行Lambdaトリガー
初回ログイン時にAWS Lambdaがユーザーに代わって移行前のユーザー認証基盤にログインし、取得したログイン情報をUserPoolに渡すやり方です。  
パスリセも。


=== APIを用いたカスタムのユーザー移行スクリプト
CognitoのAPIを利用し、新規作成時同様にユーザーを作成します。



=={sec-ext} ユーザー移行方法の選び方
要件ごとに適したユーザー移行方法を紹介します。  

これまで紹介した3つの方法のうち、CSVファイルからのインポートとカスタムのユーザー移行スクリプトには制約があります。まず2つの手段で要件が満たせるかを確認し、それでダメならユーザー移行Lambdaトリガーを利用するのがよいでしょう。  
CSVファイルからのユーザーのインポートとカスタムのユーザー移行スクリプトで対応できない要件は以下の通りです。

* パスワードの移行
* ユーザーに代わって移行前のIDトークンを取得し、外部サービスに対してUserPoolのIDトークンと紐つけるように依頼すること

上記の要件が不要な場合（例えばユーザーに対してパスワードリセットの案内を案内をガイドできる場合）、CSVファイルからユーザーをインポートする方法で問題ありません。  
そうでない場合はユーザー移行Lambdaトリガーを実装します。次章にて詳しく解説します。