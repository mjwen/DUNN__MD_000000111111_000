#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include "helper.h"

#define MY_PI 3.1415926535897932

// Symmetry functions taken from:

typedef double (*CutoffFunction)(double r, double rcut);
typedef double (*dCutoffFunction)(double r, double rcut);


class Descriptor
{
  public:

		std::vector<std::string> name;    // name of each descriptor
		std::vector<int> starting_index;  // starting index of each descriptor
                                      // in generalized coords
		std::vector<double**> params;     // params of each descriptor
		std::vector<int> num_param_sets;  // number of parameter sets of each descriptor
		std::vector<int> num_params;      // size of parameters of each descriptor
    bool has_three_body;

    bool center_and_normalize;        // whether to center and normalize the data
    std::vector<double> features_mean;
    std::vector<double> features_std;


    Descriptor();
		~Descriptor();

		// initialization helper
		void set_cutfunc(char* name);
		void add_descriptor(char* name, double** values, int row, int col);
		void set_center_and_normalize(bool do_center_and_normalize, int size,
        double* means, double* stds);

    int get_num_descriptors();

		// symmetry functions
    void sym_g1(double r, double rcut, double &phi);
    void sym_g2(double eta, double Rs, double r, double rcut, double &phi);
    void sym_g3(double kappa, double r, double rcut, double &phi);
    void sym_g4(double zeta, double lambda, double eta,
        const double* r, const double* rcut, double &phi);
    void sym_g5(double zeta, double lambda, double eta,
        const double* r, const double* rcut, double &phi);

    void sym_d_g1(double r, double rcut, double &phi, double &dphi);
    void sym_d_g2(double eta, double Rs, double r, double rcut, double &phi,
        double &dphi);
    void sym_d_g3(double kappa, double r, double rcut, double &phi, double &dphi);
    void sym_d_g4(double zeta, double lambda, double eta,
        const double* r, const double* rcut, double &phi, double* const dphi);
    void sym_d_g5(double zeta, double lambda, double eta,
        const double* r, const double* rcut, double &phi, double* const dphi);


//TODO delete; for debug purpose
    void echo_input() {
      std::cout<<"====================================="<<std::endl;
      for (size_t i=0; i<name.size(); i++) {
        int rows = num_param_sets.at(i);
        int cols = num_params.at(i);
        std::cout<<"name: "<<name.at(i)<<", rows: "<<rows<<", cols: "<<cols<<std::endl;
        for (int m=0; m<rows; m++) {
          for (int n=0; n<cols; n++) {
            std::cout<<params.at(i)[m][n]<< " ";
          }
          std::cout<<std::endl;
        }
        std::cout<<std::endl;
      }

      // centering and normalization
      std::cout<<"centering and normalizing params"<<std::endl;
      std::cout<<"means:"<<std::endl;
      for (size_t i=0; i<features_mean.size(); i++) {
        std::cout<<features_mean.at(i)<< std::endl;
      }
      std::cout<<"stds:"<<std::endl;
      for (size_t i=0; i<features_std.size(); i++) {
        std::cout<<features_std.at(i)<< std::endl;
      }

    }


	private:
		CutoffFunction cutoff;
		dCutoffFunction d_cutoff;
};


// cutoffs
inline double cut_cos(double r, double rcut) {
	if (r < rcut)
		return 0.5 * (cos(MY_PI*r/rcut) + 1);
	else
		return 0.0;
}

inline double d_cut_cos(double r, double rcut) {
	if (r < rcut)
		return -0.5*MY_PI/rcut * sin(MY_PI*r/rcut);
	else
		return 0.0;
}


//TODO correct it
inline double cut_exp(double r, double rcut) {
	if (r < rcut)
		return 1;
	else
		return 0.0;
}

inline double d_cut_exp(double r, double rcut) {
	if (r < rcut)
		return 0.0;
	else
		return 0.0;
}



#endif // DESCRIPTOR_H_


