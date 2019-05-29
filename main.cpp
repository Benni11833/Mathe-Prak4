#include "CKomplex.h"

#include <fstream>   
#include <vector>
#include <iomanip>

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

std::vector<CKomplex> fourier_trafo1(std::vector<CKomplex> werte) {
	std::vector<CKomplex> trafo_vals;	trafo_vals.resize(werte.size());
	std::vector<CKomplex> tmp;			tmp.resize(werte.size());
	CKomplex comp_fac{0,0};
	double phi{ 0.0 };
	for (int i = 0; i < werte.size(); i++) {	//cn
		tmp[i] = 0;
		for (int ii = 0; ii < werte.size(); ii++) {
			//phi = -((2 * PI*i*ii) / werte.size());
			phi = double(i)*double(ii)*double(-2)*double(PI) / double(werte.size());
			comp_fac = CKomplex{ phi };
			tmp[i] = tmp[i] + (werte[ii] * comp_fac);
		}
		trafo_vals[i] = (1 / sqrt(werte.size())) * tmp[i];
	}

	return trafo_vals;
}

std::vector<CKomplex> fourier_trafo2(std::vector<CKomplex> werte) {
	std::vector<CKomplex> trafo_vals;	trafo_vals.resize(werte.size());
	std::vector<CKomplex> tmp;			tmp.resize(werte.size());
	CKomplex comp_fac{ 0,0 };
	double phi{ 0.0 };
	for (int i = 0; i < werte.size(); i++) {	//cn
		tmp[i] = 0;
		for (int ii = 0; ii < werte.size(); ii++) {
			//phi = ((2 * PI*i*ii)/werte.size());
			phi = double(i)*double(ii)*double(2)*double(PI) / double(werte.size());
			comp_fac = CKomplex{ phi };
			tmp[i] = tmp[i] + (werte[ii] * comp_fac);
		}
		trafo_vals[i] = (1 / sqrt(werte.size())) * tmp[i];
	}

	return trafo_vals;
}

int main(){
	
	std::vector<CKomplex> vals = werte_einlesen("Daten_original.txt");

	std::vector<CKomplex> trafo_daten = fourier_trafo1(vals);
	werte_ausgeben("hin_trafo.txt", trafo_daten);
	werte_ausgeben("rueck_trafo.txt", fourier_trafo2(trafo_daten));

	//std::cin.get();
    return 0;
}