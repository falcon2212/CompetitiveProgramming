class Garner{
public:
    vector<int> x, a, p;
    int k;
    Garner(){

        for (int i = 0; i < k; ++i) {
            x[i] = a[i];
            for (int j = 0; j < i; ++j) {
                x[i] = r[j][i] * (x[i] - x[j]);

                x[i] = x[i] % p[i];
                if (x[i] < 0)
                    x[i] += p[i];
            }
        }
    }
};