PDF = cognito-userpool-in-action.pdf
PDF_TRIAL = cognito-userpool-in-action-trial.pdf

$(PDF):
	ln -f config.prod.yml config.yml && docker-compose run --rm review && open $(PDF)

trial:
	ln -f config.trial.yml config.yml && docker-compose run --rm review && open $(PDF_TRIAL)

clean:
	rm $(PDF) $(PDF_TRIAL)
