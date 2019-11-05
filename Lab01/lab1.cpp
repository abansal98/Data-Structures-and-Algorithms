unsigned int factorial (unsigned int n){
	unsigned int factorial = 1;
	for(int i = 1; i <= n; i++){
		factorial *= i;
	}
	return factorial;
}

double power (double base, unsigned int n){
	double pow = 1;
	for(int i = 0; i < n; i++){
		pow *= base;
	}
	return pow;
}

unsigned int fibonacci (unsigned int n){
	int prev = 1;
	int next = 0;
	if(n == 0){
		return 0;
	}
	for(int i = 1; i <= n; i++){
		next = prev + next;
		prev = next - prev;
	}
	return next; 
}
