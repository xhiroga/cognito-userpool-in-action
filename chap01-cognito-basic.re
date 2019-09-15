= Cognitoの基本

//abstract{
本章では、初めにAmazon Cognitoがどのようなサービスかをご紹介します。  
続いてCognitoを構成する3つのサービスに焦点を当てたあと、最後にそれらの使い分けを考えます。
//}


=={sec-ext} Amazon Cognitoとは

AWSが提供するユーザーの認証・認可を管理するためのマネージドサービスです。GCP@<fn>{b2a7e348}であればFirebase Authenticationが競合にあたります。  
モバイルアプリやWebアプリケーションに認証・認可の機能を組み込む際に導入を検討される方が多いのではないでしょうか。
一般的なユースケースで認証・認可に必要な機能に加え、エンドユーザーにAWSの一時的な認証情報を発行できるなどの特徴があります。  

//footnote[b2a7e348][Google Cloud Platform]

Amazon Cognitoは、それぞれ特性の異なる3つのサービスの総称です。次節で詳しくご紹介します。

=={sec-ext} Cognitoの3つのサービス

Amazon Cognitoには、以下の3つのサービスがあります。

 * Cognito UserPool
 * Cognito Federated Identity
 * Cognito Sync

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
もっとも、現在ではUserPool単体で認可ができるため、AWSの一時的な認証情報を与えたいケースなどに限定して利用することになります。


=== Sync

2014年7月に一般利用開始。
デバイス間でアプリケーションデータを同期するサービスです。
現在では、代わりにAWS AppSyncを利用することが公式に推奨されています。そのため、今後は利用すべきでないでしょう。本書でも以降は出てきません。


=={sec-ext} UserPoolとFederated Identity

Amazon Cognitoのサービスの概要を掴んだところで、UserPoolとFederated Identityの違いを見ていきましょう。


=== UserPoolとFederated Identityの違い

簡単に説明すると次の点が異なります。  

 * UserPoolは認証ができる。Federated Identityは認証ができない。
 * UserPoolは認可のためにJWTを返す。Federated Identityは認可のために一時的なAWSの認証情報を返す。


=== UserPoolとFederated Identityのどちらを利用すべき？

要件に応じて、UserPoolのみを利用するパターン、Federated Identityのみを利用するパターン、両方を利用するパターンがあります。まずは表（@<img>{userpool_or_federated_identity}）をご覧ください。
//image[userpool_or_federated_identity][UserPoolとFederated Identityのどちらを利用すべき？]

@<b>{パターン1}@<br>{}
ユーザー認証基盤を作成・移行し、クライアントはバックエンドのAWSリソースに直接アクセスするケースです。  
クライアント・サーバーがひとつのサービスとして提供されているケースでは、このような構成を取ることが多いのではないでしょうか。  

@<b>{パターン2}@<br>{}
ユーザー認証基盤を作成・移行するが、バックエンドのリソースへのアクセスはAPIサーバーなどを経由するケースです。  

@<b>{パターン3}@<br>{}
クライアントがバックエンドのAWSリソースに直接アクセスする手段だけが欲しい！というケースです。  
ユーザー認証には既存ののシステムを利用するか、またはFacebookなどのOpenIDプロバイダーを用いるのでしょう。  

@<b>{パターン4}@<br>{}
ユーザー認証基盤を作成・移行せず、AWSのリソースに直接アクセスすることもない、というケースです。既存の複数のAPIサーバーをひとつの認可でまとめて提供したいケースなどでしょうか。@<br>{}
一応、既存のユーザー認証基盤をUserPoolと連携させることで、UserPoolを認可サーバーとして利用できます。しかし、このケースではAWSを利用しなくてもいいかもしれません。  
サードパーティの認可サービスも検討するのはいかがでしょうか。@<fn>{35f80250}  
//footnote[35f80250][Authleteなど。]

まとめると、ユーザー認証基盤にはUserPoolを利用すればよく、AWSの一時的な認証情報を発行したい場合はFederated Identityを利用すればいいことが分かりました。  
次章では、UserPoolを利用したシステムのアーキテクチャと、その開発と設定のポイントをご紹介します。
