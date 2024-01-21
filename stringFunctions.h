#pragma once
void strCpy(const char* source, char* dest)
{
	if (!source || !dest)
		return;
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}
int strCmp(const char* first, const char* second)
{
	if (!first || !second)
		return 0;

	while ((*first) && (*second) && ((*first) == (*second)))
	{
		first++;
		second++;
	}

	return (*first - *second);
}
size_t strLen(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str)
	{
		result++;
		str++;
	}
	return result;
}