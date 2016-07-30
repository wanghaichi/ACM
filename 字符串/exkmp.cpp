/*********exkmp模板********************

求解s1的任意后缀与s2的最长公共前缀
next中保存s2的任意后缀与其自身的最长公共前缀
调用方法为：
Next[0] = 0;
exkmp(s2+1, s2, Next, Next + 1); //求出next数组
exkmp(s1, s2, Next, ex); //将结果储存在ex数组中
**************************************/
void exkmp(char s1[], char s2[], int next[], int ex[]){
	int i, j, p;
	for(i = 0, j = 0, p = -1; s1[i] != '\0'; i ++, j++, p--){
		if(p == -1){
			j = 0;
			do
				p++;
			while(s1[i+p] != '\0' && s1[i+p] == s2[j+p]);
			ex[i] = p;
		}
		else if (next[j] < p) ex[i] = next[j];
		else if (next[j] > p) ex[i] = p;
		else{
			j = 0;
			while(s1[i+p] != '\0' && s1[i + p] == s2[j+p])
				p ++;
			ex[i] = p;
		}
	}
	ex[i] = 0;
}
