= Cognitoの基礎知識

//abstract{
UserPoolとFederated Identityの違いとか
//}

Draft

=={sec-ext} Cognitoの3つのサービス

AWS Cognitoには、以下の3つのサービスがあります。本書では特に、Cognito UserPoolについて解説します。

* Cognito UserPool
* Cognito Federated Identity
* Cognito Sync
（以降、サービス名の `Cognito`は省略）

それぞれ、主に以下の機能を備えています。

=== UserPool
2016年7月に一般利用開始。
Identity Providerと呼ばれることもあります。

* ユーザーIDやメールアドレスなどのデータベース
* メールアドレスなどを使った普通のサインイン
* Facebookなどを使ったソーシャルサインイン(2017年8月に追加)
* OAuth2.0に準拠したAPIへのアクセスの認可(2017年12月に追加)
* CSVのインポート、またはAWS Lambdaトリガーによるユーザーの移行

多くのケースではUserPoolだけを利用していれば問題ありません。

=== Federated Identity
2014年7月に一般利用開始。
IDプール、Cognito Identityと呼ばれることもあります。

* Facebookなどを使ったソーシャルサインイン
* AWS認証情報（アクセスキー・シークレットキー・セッショントークン）の提供

独自のユーザー情報を持つことができないので、UserPoolやFacebookなどと組み合わせて利用することになります。
もっとも、現在ではUserPool単体で認可もできるので出番は少ないです。エンドユーザーにS3やDynamoDBのリソースに触るための認可を与えたいときに利用できます。

=== Sync
2014年7月に一般利用開始。
デバイス間でアプリケーションデータを同期するサービスです。
現在では、代わりにAWS AppSyncを利用することが公式に推奨されています。


=={sec-ext} UserPoolのユースケース


UserPool
* 
Federeated Identity
* 最近では使わない
* AWSの認証を触りたいケース（どんなときだ？）
Sync


ユーザーディレクトリ、ソーシャル連携・OAuth対応、他要素認証など
SDKがある
圧倒的に安い

競合サービス, firebaseとかauth0とか
awsでインフラを統一したい、とかオススメ



骨子
UserPoolについて解説する
他のサービスと比べるとこんな感じ





