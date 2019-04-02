#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Struct of the "map" of each string, with the string and its value */
typedef struct strmap {
	char str[1024];
	int val;
} StrMap;

/** Reads the strings of the file fp, storing each word in vec. */
int readFile(FILE* fp, char*** vec) {
	if (fp == NULL)
		return -1;

	int qtt = 0;

	char* tmp;
	while(fscanf(fp, "%m[^\n\r] ", &tmp) != EOF) {
		*vec = realloc(*vec, (qtt+1) * sizeof(char*));
		(*vec)[qtt] = tmp;
		qtt++;
	}

	return qtt;
}

/** Compare function for the vector of strings */
int cmpfunc(const void* a, const void* b) {
	return strcmp(*(const char**)a, *(const char**)b);
}

/** Map all the strings of strvec into strmap. */
int mapStrings(StrMap** strmap, char** strvec, int qtt) {

	if (strmap == NULL)
		return -1;

	*strmap = realloc(*strmap, sizeof(StrMap));
	(*strmap)[0].val = 0;
	strcpy((*strmap)[0].str, strvec[0]);


	int id = 1;
	for (int i = 1; i < qtt; i++) {
		if (strcmp(strvec[i], strvec[i-1])) {
			id++;

			*strmap = realloc(*strmap, id * sizeof(StrMap));
			(*strmap)[id-1].val = id-1;
			strcpy((*strmap)[id-1].str, strvec[i]);
		}
	}

	return id;
}

/** Returns the id of the string "word", stored on the map */
int getId(StrMap* strmap, char* word, int mapSize) {
	for (int i = 0; i < mapSize; i++) {
		if (!strcmp(word, strmap[i].str))
			return i;
	}

	return -1;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Incorrect exection. Usage:\x1b[31m ./main text1.txt text2.txt \x1b[0m\n");
		return 1;
	}

	FILE* fp1 = fopen(argv[1], "r");
	if (fp1 == NULL) {
		printf("Invalid text given.\n");
		return 1;
	}

	FILE* fp2 = fopen(argv[2], "r");
	if (fp2 == NULL) {
		printf("Invalid text given.\n");
		return 1;
	}

	char **str1 = NULL, **str2 = NULL;

	int qtt1 = readFile(fp1, &str1);
	int qtt2 = readFile(fp2, &str2);
	int qtt = qtt1 + qtt2;

	char **str = malloc(qtt * sizeof(char*));

	for (int i = 0; i < qtt1; i++) {
		str[i] = malloc(sizeof(char*));
		strcpy(str[i], str1[i]);
	}

	for (int i = qtt1; i < qtt; i++) {
		str[i] = malloc(sizeof(char*));
		strcpy(str[i], str2[i - qtt1]);
	}

	qsort(str, qtt, sizeof(char*), cmpfunc);

	StrMap* strmap = NULL;
	int wordCount = mapStrings(&strmap, str, qtt);

	int w = 1;
	Error error;

	/* Creates the graph of the first text */
	Graph* g1 = graph_create(wordCount, sizeof(int), true, &error);
	for (int i = 1; i < qtt1; i++) {
		int u = getId(strmap, str1[i-1], wordCount);
		int v = getId(strmap, str1[i], wordCount);
		graph_addEdge(g1, u, v, &w, &error);
	}

	/* Creates the graph of the second text */
	Graph* g2 = graph_create(wordCount, sizeof(int), true, &error);
	for (int i = 1; i < qtt2; i++) {
		int u = getId(strmap, str2[i-1], wordCount);
		int v = getId(strmap, str2[i], wordCount);
		graph_addEdge(g2, u, v, &w, &error);
	}

	/* ********************************************************* */

	/* Counts the words in common */
	int totalNodes = 0, nodesInCommon = 0;
	for (int i = 0; i < wordCount; i++) {
		bool is1 = graph_vertexIsUsed(g1, i, &error);
		bool is2 = graph_vertexIsUsed(g2, i, &error);

		totalNodes += is1 || is2;
		nodesInCommon += is1 && is2;
	}

	/* Counts the connections between the words */
	int totalEdges = 0, edgesInCommon = 0;
	for (int u = 0; u < wordCount; u++) {
		for (int v = 0; v < wordCount; v++) {
			if (u == v) {
				continue;
			}

			bool is1 = graph_edgeIsSet(g1, u, v, &error);
			bool is2 = graph_edgeIsSet(g2, u, v, &error);

			totalEdges += is1 || is2;
			edgesInCommon += is1 && is2;
		}
	}

	/* Calculate and print the similarity of texts */
	double similarity = (4 * (edgesInCommon / (double)totalEdges) + 6 * (nodesInCommon / (double)totalNodes)) / 10;
	printf("Similarity between texts: %.2lf%%\n", 100 * similarity);

	/* ************************ */
	/*     Free memory used.    */
	graph_destroy(g1, &error);
	graph_destroy(g2, &error);

	free(strmap);

	for (int i = 0; i < qtt; i++)
		free(str[i]);
	free(str);

	for (int i = 0; i < qtt1; i++)
		free(str1[i]);
	free(str1);

	for (int i = 0; i < qtt2; i++)
		free(str2[i]);
	free(str2);

	fclose(fp1);
	fclose(fp2);
}