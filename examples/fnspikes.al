fn <start>-><initEnd>:
	if (file == NULL) {
		emit:<filleDoesntExist>
		huh = 'duh';
	} else {
		wait:<fileWrited>:cout(2);
		isNull = huh == NULL;
	}
