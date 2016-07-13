ll exgcd(ll a, ll b, ll& x, ll& y) { //扩展欧几里得算发，求解ax + by = d = gcd(a, b)的解
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll d = exgcd(b, a%b, x, y), tmp; 
	//x = y', y = x' - a / b * y'
	tmp = x; 
	x = y;
	y = tmp - a / b*y;
	return d;
}
//求解模线性方程，ax = b (mod n) 
//该方程当且仅当 b|d 时有d个解，每个解之间相差n/d
void modular_linear(ll a, ll b, ll n) { 
	if (b == 0) {
		puts("0");
		return;
	}
	ll d, x, y;
	d = exgcd(a, n, x, y);
	if (b % d != 0) {
		printf("FOREVER\n");
	}
	else {
		x = (x*b / d) % n; 
		x = (x % (n / d) + n / d) % (n / d); //求得最小的正数解 其余解为 (x+ i * n / d) % n (i = 1,2,3...)
		printf("%I64d\n", x);
	}
}
