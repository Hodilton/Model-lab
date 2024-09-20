#ifndef VECTORS_H
#define VECTORS_H

#include "./stdafx.h"
#include "./my_random.h"
#include "./file work/include/json/json.hpp"

template<typename T>
class Vectors {
private:
	int num_elem;
	int num_vec;
	std::pair<unsigned short, unsigned short> limits;

public:
	std::vector<std::vector<T>> vectors;

	void fill() {
		vectors.clear();
		vectors.resize(num_vec);

		auto gen = my_random::Factory::Create<int>();
		for (int i = 0; i < num_vec; ++i) {
			vectors[i].resize(num_elem);
			for (int j = 0; j < num_elem; ++j) {
				vectors[i][j] = gen->Get(limits.first, limits.second);
			}
		}
	}

	std::vector<T> sum_each_vector() const {
		std::vector<T> sums;
		for (const auto& vec : vectors) {
			T sum = std::accumulate(vec.begin(), vec.end(), static_cast<T>(0));
			sums.push_back(sum);
		}
		return sums;
	}

	friend std::ostream& operator<<(std::ostream& out, const Vectors<T>& v) {
		for (const auto& vec : v.vectors) {
			out << endl;
			for (const auto& elem : vec) {
				out << elem << " ";
			}
		} out << endl;

		return out;
	}

	using json = nlohmann::json;
	friend void to_json(json& j, const Vectors<T>& v) {
		j = json{
			{"num_elem", v.num_elem},
			{"num_vec", v.num_vec},
			{"limits", {v.limits.first, v.limits.second}}
		};
	}
	friend void from_json(const json& j, Vectors<T>& v) {
		j.at("num_elem").get_to(v.num_elem);
		j.at("num_vec").get_to(v.num_vec);

		std::array<unsigned short, 2> limits_arr;
		j.at("limits").get_to(limits_arr);
		v.limits = { limits_arr[0], limits_arr[1] };
	}
};

#endif // !VECTORS_H