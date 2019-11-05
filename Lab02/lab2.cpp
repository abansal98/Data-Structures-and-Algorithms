unsigned int factorial (unsigned int n){
	if(n == 1 || n == 0) return 1;
	n = n * factorial(n - 1);
	return n;
}


double power (double base, unsigned int n){
	if(n == 0) return 1;
	if(n == 1) return base;
	base = base * power(base, n - 1);
	return base;
}


unsigned int fibonacci (unsigned int n){
	if(n == 0) return 0;
	if(n == 1) return 1;
	n = fibonacci(n - 1) + fibonacci(n - 2);
	return n;
}
