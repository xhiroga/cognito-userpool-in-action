# AWS Cognito UserPool ユーザー移行入門（仮題）

PDF is here.  
https://hiroga-cognito-user-migration.s3-ap-northeast-1.amazonaws.com/cognito_user_migration.pdf

# Run
build at local
```
# trial
ln -f config.trial.yml config.yml
docker-compose run --rm review && open cognito_user_migration.pdf

# prod
ln -f config.prod.yml config.yml
docker-compose run --rm review && open cognito_user_migration.pdf
```

#References
https://kauplan.org/reviewstarter/
