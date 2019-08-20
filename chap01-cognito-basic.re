= Cognitoの基本

//abstract{
AWS Cognitoには、役割の違う3つのサービスがあります。本章ではそれらのサービスを紹介し、その上でどうしてCognito UserPoolを利用すべきかについて解説します。
//}


=={sec-ext} Cognitoの3つのサービス

AWS Cognitoには、以下の3つのサービスがあります。

 * Cognito Federated Identity
 * Cognito Sync
 * Cognito UserPool

（以降、サービス名の @<b>{Cognito}は省略）

それぞれ、主に以下の機能を備えています。

=== Federated Identity

2014年7月に一般利用開始。
IDプール、Cognito Identityと呼ばれることもあります。

 * Facebookなどを使ったソーシャルサインイン
 * AWS認証情報（アクセスキー・シークレットキー・セッショントークン）の提供

独自のユーザー情報を持つことができないので、UserPoolやFacebookなどと組み合わせて利用することになります。
もっとも、現在ではUserPool単体で認可ができるため、認可をグループごとに与えたいケースなどに限定して利用されることになります。

=== Sync

2014年7月に一般利用開始。
デバイス間でアプリケーションデータを同期するサービスです。
現在では、代わりにAWS AppSyncを利用することが公式に推奨されています。そのため、今後は利用すべきでないでしょう。本書でも以降は出てきません。

=== UserPool

2016年7月に一般利用開始。
Identity Providerと呼ばれることもあります。@<fn>{DC0092D6-2FE6-4F34-967F-EABA1E637EFE}以下の機能を備えています。

 * ユーザーIDやメールアドレスなどのデータベース
 * メールアドレスなどを使った普通のサインイン
 * Facebookなどを使ったソーシャルサインイン(2017年8月に追加)
 * OAuth2.0に準拠したAPIへのアクセスの認可(2017年12月に追加)
 * CSVのインポート、またはAWS Lambdaトリガーによるユーザーの移行

多くのケースではUserPoolだけを利用していれば問題ありません。

//footnote[DC0092D6-2FE6-4F34-967F-EABA1E637EFE][Identityという単語はFederated Identityにも入っていて紛らわしいのですが、要はProviderという単語が入っていればUserPoolのことを指しています。]


=={sec-ext} UserPoolを利用したアーキテクチャ

（執筆中...）

メモ:
* ユースケースというより、モバイル/PWAにしぼったアーキテクチャ
* IAM認証かUserPool認証か、だけあればいいと思う。
* 普通のWebサイトやエンタープライズについてはBlackBelt見たほうがいい

