#ifndef WCDARECZ_H
#define WCDARECZ_H

#include <vector>

void DealWCDAEvent(const std::vector<int>& cell_ig, const std::vector<double>& cell_pe, const std::vector<double>& cell_t,
		std::vector<double>& wcda_clean_x, std::vector<double>& wcda_clean_y, std::vector<double>& wcda_clean_pe, 
		std::vector<int>& wcda_clean_ig, std::vector<double>& wcda_clean_t, double* evrec);


#endif
