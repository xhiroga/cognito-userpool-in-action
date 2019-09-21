# Amazon Cognito UserPool実践入門

Amazon Cognito UserPoolの基本からユーザー移行Lambdaトリガーまでをカバーした、UserPoolの利用を検討している人、現在UserPoolを理解しており、知識を整理したい人に捧げる一冊です。Cognito UserPoolのユーザー移行を業務で経験した著者が、これからデビューする人のハードルを下げたい気持ちで執筆しました。  
本書はCognito UserPoolの基本を抑える前半と、ユーザー移行の基本を抑える後半に分かれています。アーキテクチャや表を盛り込み、AWSのドキュメントを読み込む前に頭の中に地図を作ることができるように心がけました。

# 頒布用
https://hiroga-techbookfest.s3-ap-northeast-1.amazonaws.com/d2f64fa7-09cc-4570-b05d-dddd33248aa2

# Run
build at local
```
# trial
ln -f config.trial.yml config.yml && docker-compose run --rm review && open cognito_userpool_in_action_trial.pdf

# prod
ln -f config.prod.yml config.yml && docker-compose run --rm review && open cognito_userpool_in_action.pdf
```

#References
https://kauplan.org/reviewstarter/
