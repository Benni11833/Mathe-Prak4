#include "CKomplex.h"

#include <fstream>   
#include <vector>
#include <iomanip>
#include <float.h>

#define PI 3.14159265358979323846264338327950288419


void print_vec(const std::vector<CKomplex>& vals) {
	for (int i = 0; i < vals.size(); i++) {
		if (i % 6 == 0 && i != 0)
			std::cout << std::endl;
		std::cout << std::setw(10) << vals[i];
	}
	std::cout << std::endl;
}

std::vector<CKomplex>  werte_einlesen(const char *dateiname)
{
	int i, N, idx;
	double re, im;
	std::vector<CKomplex> werte;
	// File oeffnen
	std::ifstream fp;
	fp.open(dateiname);
	if (!fp.is_open())
		std::cerr << "Datei " << dateiname << " konnte nicht geoeffnet werden...\n";
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

void werte_ausgeben(const char *dateiname, std::vector<CKomplex> werte, double epsilon = -1.0)
{
	int i;
	int N = werte.size();
	// File oeffnen
	std::ofstream fp;
	//fp.precision(10);
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

std::vector<CKomplex> fourier_trafo(bool hin_trafo, std::vector<CKomplex> werte) {
	unsigned int N{ werte.size() };
	std::vector<CKomplex> trafo_vals;	trafo_vals.resize(N);
	std::vector<CKomplex> tmp;			tmp.resize(N);
	CKomplex comp_fac{0,0};
	double phi{ 0.0 };
	for (int i = 0; i < N; i++) {	//cn
		tmp[i] = CKomplex{ 0,0 };
		for (int ii = 0; ii < N; ii++) {
			//phi = -((2 * PI*i*ii) / werte.size());
			if(hin_trafo)
				phi = (double(i)*double(ii)*double(-2)*double(PI)) / double(N);
			else
				phi = (double(i)*double(ii)*double(2)*double(PI)) / double(N);
			comp_fac = CKomplex{ phi };
			tmp[i] = tmp[i] + (werte[ii] * comp_fac);
		}
		trafo_vals[i] = (1 / sqrt(N)) * tmp[i];
	}

	return trafo_vals;
}

long double getMax(long double x, long double y) {
	if (x > y)
		return x;
	else
		return y;
}

long double max_abweichung(std::vector<CKomplex>& ck1, std::vector<CKomplex>& ck2) {
	long double max = 0.0L;
	if (ck1.size() == 0 || ck2.size() == 0) {
		std::cerr << "Vectoren sind leer.\n";
		return -1;
	}
	else {
		for (int i = 0; i < ck1.size(); i++) {
			if (abs(ck1[i].re() - ck2[i].re()) > max) {
				max = abs(ck1[i].re() - ck2[i].re());
			}
		}
	}
	return max;
}

int main(){
	
	std::vector<CKomplex> vals = werte_einlesen("Daten_original.txt");
	std::vector<CKomplex> hin_trafo = fourier_trafo(true, vals);
	//std::vector<CKomplex> rueck_trafo = fourier_trafo(false, hin_trafo);

	werte_ausgeben("standard_eps_hin.txt", hin_trafo);
	werte_ausgeben("0.1_eps_hin.txt", hin_trafo, 0.1);
	werte_ausgeben("1.0_eps_hin.txt", hin_trafo, 1.0);

	hin_trafo = werte_einlesen("standard_eps_hin.txt");
	hin_trafo = fourier_trafo(false, hin_trafo);
	std::cout << "Maximale Abweichung bei Standard-Epsilon: " << max_abweichung(vals, hin_trafo) << std::endl;
	hin_trafo = werte_einlesen("0.1_eps_hin.txt");
	hin_trafo = fourier_trafo(false, hin_trafo);
	std::cout << "Maximale Abweichung bei epsilon=0.1: " << max_abweichung(vals, hin_trafo) << std::endl;
	hin_trafo = werte_einlesen("1.0_eps_hin.txt");
	hin_trafo = fourier_trafo(false, hin_trafo);
	std::cout << "Maximale Abweichung bei epsilon=1.0: " << max_abweichung(vals, hin_trafo) << std::endl;

	system("pause");
    return 0;
}

/*
TODO
-abweichungen berechnen(evtl eigene Funk machen)
*/