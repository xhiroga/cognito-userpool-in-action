#!/bin/sh -e
aws s3 cp cognito_user_migration.pdf s3://hiroga-cognito-user-migration/cognito_user_migration.pdf --acl public-read
