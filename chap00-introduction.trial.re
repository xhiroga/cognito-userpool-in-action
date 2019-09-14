= はじめに

本書は体験版です。実践のポイントやアーキテクチャ・実装の解説は、技術書典での頒布版をご覧いただければ幸いです。
@<br>{}

ユーザー認証基盤の構築・運用は、Webサービスに関わる人なら誰でも悩んだことがあると思います。それ自体がユーザーに提供する価値につながるわけではないが、適切な実装をしなければサービス自体の運用や、その後の拡張の妨げになってしまうからです。
Amazon Cognitoは、そうしたユーザー認証基盤のマネージドサービスの一つです。ユーザー認証基盤としての基本的な機能を備え、AWSのサービスとの親和性が高いことから、導入している・導入を検討している方も多いかと思います。  
本書では、Amazon Cognito UserPoolとユーザー移行に関する概要と実践から得られた知見を紹介します。
@<br>{}
@<br>{}

=={sec-ext} 対象読者

AWSのマネージドサービスの利用経験がある読者を想定しています。また、実際にAWSのマネジメントコンソールを触りながら読んだ方が分かりやすい内容になっています。
本書で紹介している設定は基本的にAmazon Cognitoの無料利用枠内で試せますので、ぜひ積極的に試してみてください。
@<br>{}
@<br>{}

=={sec-ext} 本書の構成

まずはAmazon Cognitoについて簡単に解説し、次にAmazon Cognitoを利用したアーキテクチャとオススメの設定をご紹介します。
続いて、、UserPoolへのユーザー移行について扱います。最終章では、筆者が関わったケースを通してユーザー移行Lambdaの構築のハマりどころを実際に見ていきます。
@<br>{}
@<br>{}

=={sec-ext} 意見と質問

本書はAWSドキュメントやサポートに確認した内容をもとに執筆していますが、誤りや不正確な表現に気づかれることもあるかと思います。また、本書で紹介するやり方よりも更によいやり方をご存知の方もいるかもしれません。
そうした点については、今後の版で随時更新させていただきたいのでお知らせいただけると幸いです。ご意見だけでなく質問も大歓迎です。連絡先を以下に記します。

 * Mail: hiroga1030@gmail.com
 * Twitter: @hiroga_cc