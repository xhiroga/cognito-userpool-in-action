= 実践ユーザー移行

//abstract{
ユーザー移行Lambdaトリガーを組み込んだアーキテクチャを把握したあと、開発のポイントを見ていきます。
//}


=={sec-ext} ユーザー移行Lambdaトリガーのアーキテクチャ
ユーザー移行Lambdaトリガーの処理フロー（@<img>{architecture_1}）をご紹介します。  

//image[user_migration_lambda][ユーザー移行Lambdaトリガーの処理フロー][scale=0.8]

Cognitoはエンドユーザーからサインインを受けたとき、そのユーザーがユーザーディレクトリ内で見つからなければユーザー移行用のLambdaを呼び出します。  
ユーザー移行用のLambdaの実装は開発者に委ねられています。基本的には次の2つの機能を実装します。  

 1. 既存ユーザーがUserPoolに初めてサインインした場合、移行前のユーザー認証基盤に代わりにログインし、ユーザー情報を取得してUserPoolに返却する
 2. 移行していない既存ユーザーがUserPoolにパスワードリセットをリクエストしたとき、ユーザーの代わりに既存のユーザー認証基盤にパスワードリセットをリクエストする。

設計上の注意点として、移行前のユーザー認証基盤とUserPoolのユーザー情報、ログインエイリアス、パスワード制約などを整合させることが挙げられます。  
例えば移行前のユーザー認証基盤ではパスワードは6文字以内だったのが、UserPoolでは8文字以内に設定していた場合、6文字のパスワードを設定しているユーザーはUserPoolに作成されません。エンドユーザーからは、サインインが何度試しても失敗するように見えてしまいます。  

UserPoolのプロパティを移行前のユーザー認証基盤と突合し、テストケースを広く取って予防するようにしましょう。  

なお、移行前のユーザー認証基盤を外部サービスの認証のためにOIDCなどで公開している場合、UserPoolが移行前のユーザー認証基盤と同じIDトークンを返すことは当然できません。  
移行前後のIDトークンを外部サービスの側で紐付ける必要が出てきます。第5章を参考にしてください。


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
 3. AWS Lambda リソースポリシー: UserPoolがAWS Lambdaを呼び出すための許可を与える

3.のAWS Lambdaリソースポリシーは、普段マネジメントコンソールを触っていると意識する機会が少ないと思います。AWSのリソースごとのアクセス権限の設定を指します。  
実は、マネジメントコンソールからUserPoolにユーザー移行Lambdaトリガーを設定する場合、Lambdaリソースポリシーは自動で設定されるようになっています。したがって、デプロイをCLIやIaCで管理する場合は管理する場合は注意してください。

もう一点、とても大事なポイントがあります。2019-09-08時点で、CloudFormationはUserPoolへのユーザー移行Lambdaトリガーの設定に対応していません。  
したがって、UserPool本体をCloudFormationで管理している場合、UserPoolへのユーザー移行Lambdaトリガーの設定だけはCLIなどで設定するようにしてください。

CloudFormationとAWS CLIを併用してユーザー移行Lambdaトリガーをデプロイするための設定を以下に示します。参考にしてください。

```
# ココにソース
```
