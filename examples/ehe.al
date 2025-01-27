fn <start>-><initEnd>:
	if (file == NULL) {
		emit:<filleDoesntExist>
	} else {
		wait:<fileWrited>:cout(2);
	}
