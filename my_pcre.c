#define PCRE2_CODE_UNIT_WIDTH 8

#include "pcre2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("usage: [%s] [input path]\n", argv[0]);
		return 0;
	}
	pcre2_code *re = NULL;
	pcre2_match_data *match_data = NULL;
	PCRE2_SIZE erroffset;
	int errorcode;
	int rc;
	int num;
	char strTemp[255];

	FILE *fp = NULL;
	if (fopen_s(&fp, argv[1], "r") != 0)
	{
		printf("no file found\n");
		return 0;
	}

	fscanf_s(fp, "%d", &num);
	fgetc(fp);

	//Problem 1

	PCRE2_SPTR pattern1 = (PCRE2_SPTR)"(?>010|02|031|016|019)-\\d{3,4}-\\d{4}$"; // write regular expression here
	while (num--)
	{
		fgets(strTemp, sizeof(strTemp), fp);
		PCRE2_SPTR input = (PCRE2_SPTR)strTemp;

		re = pcre2_compile(pattern1, -1, 0, &errorcode, &erroffset, NULL);

		if (re == NULL)
		{
			PCRE2_UCHAR8 buffer[120];
			(void)pcre2_get_error_message(errorcode, buffer, 120);
			/* Handle error */
			return 0;
		}

		match_data = pcre2_match_data_create(20, NULL);
		rc = pcre2_match(re, input, -1, 0, 0, match_data, NULL);

		// match result
		if (rc == 1)
			printf("Y\n");
		else
			printf("N\n");
	}

	//Problem 2

	fscanf_s(fp, "%d", &num);
	fgetc(fp);

	PCRE2_SPTR pattern2 = (PCRE2_SPTR)"(?>\\d| |.|-)\\[(?>[1-2][0-9]|30|[1-9])\/Apr\/2018\]\\s\"GET\\s\/admin\\s"; // write regular expression here
	while (num--)
	{
		fgets(strTemp, sizeof(strTemp), fp);
		PCRE2_SPTR input = (PCRE2_SPTR)strTemp;

		re = pcre2_compile(pattern2, -1, 0, &errorcode, &erroffset, NULL);

		if (re == NULL)
		{
			PCRE2_UCHAR8 buffer[120];
			(void)pcre2_get_error_message(errorcode, buffer, 120);
			/* Handle error */
			return 0;
		}

		match_data = pcre2_match_data_create(20, NULL);
		rc = pcre2_match(re, input, -1, 0, 0, match_data, NULL);

		// match result
		if (rc == 1)
			printf("Y\n");
		else
			printf("N\n");
	}

	//Problem 3

	fscanf_s(fp, "%d", &num);
	fgetc(fp);

	//PCRE2_SPTR pattern = (PCRE2_SPTR)"\[(?>[1-9]|[12][0-9]|30)\/Apr\/2018\]\\s\D?GET\\s\/admin"; // write regular expression here
	//PCRE2_SPTR pattern = (PCRE2_SPTR)"(?>\\d| |.|-)\\[(?>[1-9]|30)\/"; // write regular expression here
	//PCRE2_SPTR pattern = (PCRE2_SPTR)"(?>\\d| |.|-)\\[(?>[1-2][0-9]|30|[1-9])\/Apr\/2018\]\\s\"GET\\s\/admin\\s"; // write regular expression here
	PCRE2_SPTR pattern3 = (PCRE2_SPTR)"424D(?>\\d|\\w){32}5000000046000000(?>\\d|\\w){44}$"; // write regular expression here
	while (num--)
	{
		fgets(strTemp, sizeof(strTemp), fp);
		PCRE2_SPTR input = (PCRE2_SPTR)strTemp;

		re = pcre2_compile(pattern3, -1, 0, &errorcode, &erroffset, NULL);

		if (re == NULL)
		{
			PCRE2_UCHAR8 buffer[120];
			(void)pcre2_get_error_message(errorcode, buffer, 120);
			/* Handle error */
			return 0;
		}

		match_data = pcre2_match_data_create(20, NULL);
		rc = pcre2_match(re, input, -1, 0, 0, match_data, NULL);

		// match result
		if (rc == 1)
			printf("Y\n");
		else
			printf("N\n");
	}

	fclose(fp);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
}