#include "CKomplex.h"

#include <fstream>   
#include <vector>
#include <iomanip>

std::vector<CKomplex>  werte_einlesen(const char *dateiname)
{
	int i, N, idx;
	double re, im;
	std::vector<CKomplex> werte;
	// File oeffnen
	std::ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i<N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const char *dateiname, std::vector<CKomplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
	// File oeffnen
	std::ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << std::endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << std::endl;
	// File schliessen
	fp.close();
}

int main(){

	std::vector<CKomplex> vals = werte_einlesen("Daten_original.txt");

	for (int i = 0; i < vals.size(); i++) {
		if (i % 6 == 0 && i != 0)
			std::cout << std::endl;
		std::cout << std::setw(10) << vals[i];
	}
	std::cout << std::endl;

	werte_ausgeben("above_15.txt", vals, 15);

	std::cin.get();
    return 0;
}