#include <cosma/environment_variables.hpp>
#include <algorithm>

bool cosma::env_var_defined(const char* var_name) {
    char* var = getenv (var_name);
    return var != nullptr;
}

bool cosma::get_bool_env_var(std::string name, bool default_value) {
    char* var;
    var = getenv(name.c_str());
    bool value = default_value;
    if (var != nullptr) {
        std::string s(var);
        std::transform(s.begin(), s.end(), s.begin(), 
            [&](char c) {
                return std::toupper(c);
            }
        );
        value = (s == "ON");
    }
    return value;
}

int cosma::get_int_env_var(std::string name, int default_value) {
    char* var;
    var = getenv(name.c_str());
    int value = default_value;
    if (var != nullptr)
        value = std::atoi(var);
    return value;
}

int cosma::gpu_streams() {
    return get_int_env_var(env_var_names::gpu_n_streams,
                           env_var_defaults::gpu_n_streams);
}

int cosma::gpu_max_tile_m() {
    return get_int_env_var(env_var_names::gpu_tile_m,
                           env_var_defaults::gpu_tile_m);
}

int cosma::gpu_max_tile_n() {
    return get_int_env_var(env_var_names::gpu_tile_n,
                           env_var_defaults::gpu_tile_n);
}

int cosma::gpu_max_tile_k() {
    return get_int_env_var(env_var_names::gpu_tile_k,
                           env_var_defaults::gpu_tile_k);
}

bool cosma::get_adapt_strategy() {
    return get_bool_env_var(env_var_names::adapt_strategy,
                            env_var_defaults::adapt_strategy);
}

bool cosma::get_overlap_comm_and_comp() {
    return get_bool_env_var(env_var_names::overlap,
                            env_var_defaults::overlap);
}

// reads the memory limit in MB per rank
// and converts the limit to #elements that each rank is allowed to use
template <typename T>
long long cosma::get_cpu_max_memory() {
    char* var;
    var = getenv(env_var_names::cpu_max_memory.c_str());
    long long value = env_var_defaults::cpu_max_memory;
    long long megabytes = env_var_defaults::cpu_max_memory;
    if (var != nullptr) {
        megabytes = std::atoll(var);
        // from megabytes to #elements
        value = megabytes * 1024LL * 1024LL / sizeof(T);
    }

    return value;
}

// template instantiation of get_cpu_max_memory()
template long long cosma::get_cpu_max_memory<float>();
template long long cosma::get_cpu_max_memory<double>();
template long long cosma::get_cpu_max_memory<std::complex<float>>();
template long long cosma::get_cpu_max_memory<std::complex<double>>();
