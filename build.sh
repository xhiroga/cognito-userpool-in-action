set -e
docker-compose run --rm review && open cognito_user_migration.pdf
git push
open ./cognito_user_migration.pdf
