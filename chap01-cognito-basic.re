= Cognitoの基本

//abstract{
Amazon Cognitoには、役割の違う3つのサービスがあります。本章ではそれらのサービスを紹介し、その上でどうしてCognito UserPoolを利用すべきかについて解説します。
//}


=={sec-ext} Cognitoの3つのサービス

Amazon Cognitoには、以下の3つのサービスがあります。

 * Cognito Federated Identity
 * Cognito Sync
 * Cognito UserPool

（以降、サービス名の @<b>{Cognito}は省略）

それぞれ、主に以下の機能を備えています。


=== UserPool

2016年7月に一般利用開始。3つの中では最近リリースされたサービスです。
Identity Providerと呼ばれることもあります。@<fn>{DC0092D6-2FE6-4F34-967F-EABA1E637EFE}以下の機能を備えています。

 * ユーザーIDやメールアドレスなどのデータベース
 * メールアドレスなどを使った普通のサインイン
 * Facebookなどを使ったソーシャルサインイン(2017年8月に追加)
 * OAuth2.0に準拠したAPIへのアクセスの認可(2017年12月に追加)
 * CSVのインポート、またはAWS Lambdaトリガーによるユーザーの移行

//footnote[DC0092D6-2FE6-4F34-967F-EABA1E637EFE][Identityという単語はFederated Identityにも入っていて紛らわしいのですが、要はProviderという単語が入っていればUserPoolのことを指しています。]


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


=={sec-ext} UserPoolとFederated Identity

Amazon Cognitoのサービスの概要を掴んだところで、UserPoolとFederated Identityの違いを見ていきましょう。
本節を読み終われば、自分の要件に合ったサービスがどちらなのか（または両方なのか）が分かるはずです。


=== UserPoolとFederated Identityの違い

簡単に説明すると次の点が異なります。  

 * UserPoolは認証ができる。Federated Identityは認証ができない。
 * UserPoolは認可のためにJWTを返す。Federated Identityは認可のために一時的なAWSのクレデンシャルを返す。


=== UserPoolとFederated Identityのどちらを使うべき？

要件に応じて、UserPoolのみを利用するパターン、Federated Identityのみを利用するパターン、両方を利用するパターンがあります。順に見ていきましょう。

まず、ユーザーディレクトリ・ユーザープロファイルが必要であればUserPoolを採用します。
サービスを新規作成する場合や、マネージドサービスで認証に機能を追加する場合（メールアドレス・電話番号の認証、多要素認証など）、OpenID ConnectのIDプロバイダーになる場合@<fn>{599a08c4}が当てはまるでしょう。
逆に、既存のユーザーディレクトリを移行しない場合はUserPoolを利用しません。  
//footnote[599a08c4][念のため補足すると、OpenID Connectのリライング・パーティになりたい場合、つまりGoogle認証などを利用するだけであれば、UserPoolでもFederated Identityでも可能です。]

次に、クライアントがどのようにバックエンドにアクセスするかを考えます。
バックエンドがS3やDynamoDBなどのマネージドサービスで、クライアントが直接それらのサービスにアクセスする場合は、Federated Identityを利用します。
バックエンドがアプリケーションの場合、UserPoolを利用した認証を利用するのがよいでしょう。
API GatewayとFederated Identityを組み合わせてAWSの認証情報でアクセスすることも可能です。
しかし、UserPoolを利用すれば、将来的にサードパーティのクライアントがOAuth2でバックエンドのアプリケーションを利用できるようになります。  

最後にユーザーディレクトリ・ユーザープロファイルは既存のまま、バックエンドのアプリケーションをOAuth2の仕組みで公開したい場合ですが、これはCognitoのユースケースではなさそうです。
サードパーティの認可サービスを利用するのが良いかもしれません。@<fn>{35f80250}  
//footnote[35f80250][Authleteなど。]

