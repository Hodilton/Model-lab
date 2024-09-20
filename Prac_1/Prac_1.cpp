#include "stdafx.h"

#include "./file work/file_processor.h"
#include "./Vectors.h"

int main() {
	auto vecs = file_work::File<Vectors<int>>::read(
		file_work::PathParams("./data", "vec_params", "json"));

	vecs.fill();

	auto sums = vecs.sum_each_vector();
	auto min = *(std::min_element(sums.begin(), sums.end()));

	cout << vecs << min;

	return 0;
}