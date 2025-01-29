#pragma once

// logMessage(
//	type => type of error:
//		-> 13 : ERROR
//		-> 10 : INFO
//
//	*structure => wich lines are title:
//		-> e.g.: "24" (two first lines are title, next four are actual content)
//		   in total 6 lines will be printed
//
//	... => takes strings ("") to fill each line
//		-> if 6 lines will be printed 6 strings should be provided to foo
// )
//
// example:
//	logMessage(13, "12",
//		"this is title line",
//		"this is content line 1",
//		"this is content line 2");
int logMessage(const int type, const char *structure, ...);
