# Amazon Cognito UserPool 実践入門

## 更新終了のお知らせ

本書の執筆時、筆者はCognito UserPoolおよびFederated Identityを業務で利用し、そこで知り得た知見を共有できることに喜びを感じておりました。
しかし、ここ4年ほどは別の技術を利用する機会が増え、Cognitoの最新の知見や変更を追うことが困難となってしまいました。

さらに、現在の私の関心は新しい技術に移りつつあり、公私共にそちらに力を注ぎたいと考えております。
その一方で、本書の誤りや古くなった情報を放置することは、読者の皆様にとって不利益となると考えております。

そこで、一つの決断を下しました。本書を非公開にする代わりに、本文をそのGitHubのリポジトリごと無償公開することにします。
これにより、誤りや古くなった情報について、読者の皆様で更新いただくことが可能です。

これまで有償で本書をご購入いただいた皆様には、深くお礼を申し上げます。
有償で購入いただいた書籍が無償公開されることについて、不利益を被ったと感じられる方もいらっしゃると思います。
購入者の方に公平な埋め合わせを、とも考えたのですが、販売形態や同人誌であることから現実的ではありませんでした。
代わりに、技術イベントやSNSでやり取りさせていただく際には、改めて深くお礼をさせてくださいませ。

以下、主に本書刊行時点（2019年7月）時点の情報を元に執筆しております。多少なりとも読者の方のお役に立てば幸いです。

どうぞよろしくお願いいたします。

## 商品紹介文

AWS のユーザー認証基盤サービスである Amazon Cognito UserPool について、サービス自体の基本からユーザー移行の設定までを解説します。

筆者自身も Cognito UserPool へのユーザー移行を経験した IT エンジニアです。Cognito を利用した認証・認可のアーキテクチャ自体が何パターンも考えられる上、ユーザー移行も複数のやり方があるため当初は混乱しました。
この本は、当時の自分がユーザー移行の正しい戦略を立て、成功裏にプロジェクトをリリースできるように、という一心で書きました。

同じ境遇の方の役に少しでも立てばとっても嬉しいです！

## 対象となる読者

以下に当てはまる方は、本書を読むと AWS のドキュメントの理解・処理の実装が効率化できます。
・ユーザー認証基盤の選定をしている方
・ユーザー移行を考えている方

以下に当てはまる方には、Cognito の役割を見直す効果があるかもしれません。
・現場で Amazon Cognito を利用されている方

## ビルド

```shell
make
```

## 商品リンク

- [\[更新終了につき無償公開\] Cognito UserPool ユーザー移行入門 - さわら - BOOTH](https://hiroga.booth.pm/items/1560273)
- [Cognito UserPool 実践入門 - さわら - 技術書典マーケット](https://techbookfest.org/product/6008295370260480)（販売終了）
