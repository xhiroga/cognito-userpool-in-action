PDF = cognito-userpool-in-action.pdf
PDF_TRIAL = cognito-userpool-in-action-trial.pdf

.PHONY: all

all: $(PDF) $(PDF_TRIAL)

$(PDF):
	ln -f config.prod.yml config.yml && docker-compose run --rm review

$(PDF_TRIAL):
	ln -f config.trial.yml config.yml && docker-compose run --rm review

clean:
	rm $(PDF) $(PDF_TRIAL)
