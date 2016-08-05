int prime[N], isNotPrime[N], cnt, phi[N]; //prime存放素数，phi为欧拉函数

void init() {
	memset(prime, 0, sizeof(prime));
	memset(isNotPrime, 0, sizeof(isNotPrime));
	memset(phi, 0, sizeof(phi));
	cnt = 0;
	for (int i = 2; i < N; i++) {
		if (!isNotPrime[i]) {
			prime[cnt++] = i;
			phi[i] = i - 1;
		}
		for (int j = 0; j < cnt && prime[j] * i < N; j++) {
			isNotPrime[prime[j] * i] = 1;
			if (i % prime[j] != 0) {
				phi[i*prime[j]] = phi[i] * (prime[j] - 1); //根据欧拉定理可得，当i是j的倍数时，phi[i*j] = phi[i]*(j-1); 其中i是素数
			}
			else{
				phi[i*prime[j]] = phi[i] * prime[j]; //当不是倍数时，phi[i*j] = phi[i]*(j); 其中i是素数
				break; // 保证每个数只被筛了一次
			}
		}
	}
}
