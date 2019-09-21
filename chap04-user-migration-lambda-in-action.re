= 実践ユーザー移行

//abstract{
ユーザー移行Lambdaトリガーを組み込んだアーキテクチャを把握したあと、開発のポイントを見ていきます。
//}


=={sec-ext} ユーザー移行Lambdaトリガーのアーキテクチャ
ユーザー移行Lambdaトリガーの処理フロー（@<img>{user_migration_lambda}）をご紹介します。  

//image[user_migration_lambda][ユーザー移行Lambdaトリガーの処理フロー][scale=1.0]

ユーザー移行Lambdaトリガーにおける処理の流れは以下のとおりです。

 - 1. エンドユーザーはユーザー名・パスワード（など）を用いてUserPoolにログインします。
 - 2. UserPoolにユーザーが存在しない場合、AWS Lambdaがユーザーに代わって既存の認証基盤にログインします
 - 3. 既存の認証基盤はユーザー情報を返却します。AWS LambdaはUserPoolにユーザー情報を返し、処理を終了します。
 - 4. UserPoolはユーザー情報を登録したのち、ログインに成功したことをクライアントに返却します。@<br>{}

ユーザー移行用のLambdaの実装は開発者に委ねられています。基本的には次の2つの機能を実装します。@<br>{}

 1. 既存ユーザーがUserPoolに初めてサインインした場合、移行前のユーザー認証基盤に代わりにログインし、ユーザー情報を取得してUserPoolに返却する。
 2. 移行していない既存ユーザーがUserPoolにパスワードリセットをリクエストしたとき、パスワードリセットが必要な状態のユーザーをUserPoolに返却する。@<br>{}

設計上の注意点として、移行前のユーザー認証基盤とUserPoolのユーザー情報、ログインエイリアス、パスワード制約などを整合させることが挙げられます。  
例えば移行前のユーザー認証基盤ではパスワードは6文字以内だったのが、UserPoolでは8文字以内に設定していた場合、6文字のパスワードを設定しているユーザーはUserPoolに作成されません。エンドユーザーからは、サインインが何度試しても失敗するように見えてしまいます。@<br>{}

UserPoolのプロパティを移行前のユーザー認証基盤と突合し、テストケースを広く取って予防するようにしましょう。@<br>{}


=={sec-ext} ユーザー移行Lambdaトリガーの開発

=== ユーザー移行Lambdaトリガーの実装
通常のAWS Lambdaの開発同様に開発します。SAM@<fn>{3bc85a14}などを用いてローカルでの検証環境を構築するとよいでしょう。  
ユーザー移行Lambdaトリガーの公式ドキュメント@<fn>{9d4ef6a5}にサンプルがあるので、コピーして必要な箇所を修正すると開発しやすいと思います。

//footnote[3bc85a14][Serverless Application Model@<href>{https://github.com/awslabs/serverless-application-model}]
//footnote[9d4ef6a5][ユーザー移行Lambdaトリガー@<href>{https://docs.aws.amazon.com/ja_jp/cognito/latest/developerguide/user-pool-lambda-migrate-user.html}]

=== ユーザー移行Lambdaトリガーのデプロイ
LambdaとUserPoolの接続方法に癖があるため注意しましょう。  
まず、ユーザー移行Lambdaトリガーを実際に動かすには、次の3つの設定が必要です。  

 1. UserPool: ユーザー移行Lambdaトリガーを指定する
 2. AWS Lambda: ユーザー移行Lambdaトリガー本体
 3. AWS Lambda リソースポリシー: UserPoolがAWS Lambdaによる呼び出しを許可する。

3.のAWS Lambdaリソースポリシーは、普段マネジメントコンソールを触っていると意識する機会が少ないと思います。AWSのリソースごとのアクセス権限の設定を指します。  
実は、マネジメントコンソールからUserPoolにユーザー移行Lambdaトリガーを設定する場合、Lambdaリソースポリシーは自動で設定されるようになっています。したがって、デプロイをCLIやソースコードで管理する場合は管理する場合は注意してください。

もう一点、とても大事なポイントがあります。2019-09-08時点で、CloudFormationはUserPoolへのユーザー移行Lambdaトリガーの設定に対応していません。  
したがって、UserPool本体をCloudFormationで管理したい場合、CloudFormationのカスタムリソースを利用するか、UserPoolへのユーザー移行Lambdaトリガーの設定だけはCLIなどで設定するようにしてください。
