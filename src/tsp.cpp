#include "tsp.h"

TSP::TSP(std::string file_name)
{
  std::string line;
  std::ifstream tsp_file(file_name);
  int data_points = 0;
  std::vector<std::tuple<float, float>> data;

  if (tsp_file.is_open())
  {
    std::getline(tsp_file, line);
    this->optimal_length = std::stof(line);
    std::getline(tsp_file, line);
    data_points = std::stoi(line);
    for (int i = 0; i < data_points; i++)
    {
      std::getline(tsp_file, line);
      int delim_pos = line.find(" ");
      float x = std::stof(line.substr(0, delim_pos));
      float y = std::stof(line.substr(delim_pos + 1));
      data.push_back(std::make_tuple(x, y));
    }
    tsp_file.close();
  }

  for (int i = 0; i < data_points; i++)
  {
    this->matrix.push_back(std::vector<float>(data_points, 0.0f));
  }

  for (int i = 0; i < data_points; i++)
  {
    for (int j = i + 1; j < data_points; j++)
    {
      float dx = std::get<0>(data[i]) - std::get<0>(data[j]);
      float dy = std::get<1>(data[i]) - std::get<1>(data[j]);
      this->matrix[i][j] = sqrtf(dx * dx + dy * dy);
      this->matrix[j][i] = this->matrix[i][j];
    }
  }
}

float TSP::get_optimal_length(void)
{
  return this->optimal_length;
}

float TSP::get_distance_between(int a, int b)
{
  return this->matrix[a][b];
}

int TSP::get_number_of_data_points(void)
{
  return this->matrix.size();
}

int TSP::shortest_distance_from(int src, std::unordered_set<int> &not_included)
{
  std::vector<float> distances = this->matrix[src];
  int index = 0, best = -1, best_index = -1;
  for (auto it = distances.begin(); it != distances.end(); ++it)
  {
    if (not_included.find(index) == not_included.end())
    {
      if (index != src && (best == -1 or *it < best))
      {
        best = *it;
        best_index = index;
      }
    }
    index++;
  }
  return best_index;
}

float TSP::calculate_cost_of_path(std::vector<int> &path)
{
  float total = 0.0f;
  for (unsigned int i = 0; i < path.size() - 1; i++)
  {
    total += this->matrix[path[i]][path[i + 1]];
  }
  return total + this->matrix[path.back()][path[0]];
}
