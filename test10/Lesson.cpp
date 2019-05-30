#include "Lesson.h"

Lesson::Lesson()
{
	setName(" ");
	setPerform(0);
	setScore(0);
}
Lesson::Lesson(string name, int perform,double score) {
	setName(name);
	setPerform(perform);
	setScore(score);
}

Lesson::~Lesson()
{
}