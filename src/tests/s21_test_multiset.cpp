#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>

#include "../Sorted_Container/Set_Conteiner/s21_multiset.h"

TEST(multiset, empty_const) {
  s21::multiset<double> a;
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.end(), nullptr);
  EXPECT_EQ(a.begin(), nullptr);
};

TEST(multiset, init_list_constr1) {
  s21::multiset<double> a({});
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, init_list_constr2) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 5);
};

TEST(multiset, init_copy_constr1) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  s21::multiset<double> b(a);
  double mass[] = {-3, -1.3, 3.2, 10.2, 10.2};
  int j = 0;
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(mass[j++], *i);
  }
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
};

TEST(multiset, init_copy_constr2) {
  s21::multiset<double> a;
  s21::multiset<double> b(a);
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
};

TEST(multiset, move_copy1) {
  s21::multiset<double> a;
  s21::multiset<double> b(std::move(a));
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
};

TEST(multiset, move_copy2) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  s21::multiset<double> b(std::move(a));
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.empty(), false);
  EXPECT_EQ(b.size(), 5);
};

TEST(multiset, init_move1) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  s21::multiset<double> b;
  b = std::move(a);
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.empty(), false);
  EXPECT_EQ(b.size(), 5);
};

TEST(multiset, init_move2) {
  s21::multiset<double> a;
  s21::multiset<double> b;
  b = std::move(a);
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
};

TEST(multiset, self_init1) {
  s21::multiset<double> a;
  a = std::move(a);
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, self_init2) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  a = std::move(a);
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 5);
};

TEST(multiset, begin_end) {
  s21::multiset<double> a;
  EXPECT_EQ(a.end(), a.begin());
};

TEST(multiset, check_elements) {
  s21::multiset<double> a({1.1, 2.2, 3.3, -4.4, 4.4, 4.4, 5.5});
  double mass[] = {-4.4, 1.1, 2.2, 3.3, 4.4, 4.4, 5.5};
  int j = 0;
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass[j++], *i);
  }
};

TEST(multiset, check_reverse) {
  s21::multiset<double> a({1.1, 2.2, 3.3, -4.4, 4.4, 4.4, 5.5});
  double mass[] = {5.5, 4.4, 4.4, 3.3, 2.2, 1.1, -4.4};
  int j = 0;
  for (auto i = a.end_elem(); i != a.end(); --i) {
    EXPECT_EQ(mass[j++], *i);
  }
};

TEST(multiset, max_size_empty_multiset) {
  s21::multiset<double> a;
  s21::multiset<double> b;
  EXPECT_EQ(a.max_size(), b.max_size());
};

TEST(multiset, max_size1) {
  s21::multiset<double> a({2.2, 2.2, 2.2});
  s21::multiset<double> b({3.3, 3.3});
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.max_size(), b.max_size());
};

TEST(multiset, max_size2) {
  s21::multiset<int> a({2, 2, 2});
  s21::multiset<int> b({3, 3});
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.max_size(), b.max_size());
};

TEST(multiset, max_size3) {
  s21::multiset<std::string> a;
  s21::multiset<std::string> b;
  EXPECT_EQ(a.max_size(), b.max_size());
};

TEST(multiset, clear1) {
  s21::multiset<double> a;
  a.clear();
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, clear2) {
  s21::multiset<double> a({2.2, 2.2, 2.2});
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 3);
  a.clear();
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, clear3) {
  s21::multiset<int> a;
  a.clear();
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, clear4) {
  s21::multiset<int> a({2, 2, 2});
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 3);
  a.clear();
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, clear5) {
  s21::multiset<std::string> a;
  a.clear();
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, clear6) {
  s21::multiset<std::string> a({"a", "b", "c"});
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 3);
  a.clear();
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, insert_to_empty) {
  s21::multiset<double> a;
  double mass[] = {-9., -0.3, 1.2, 3.3, 3.3, 22.2};
  int j = 0;
  a.insert(22.2);
  a.insert(3.3);
  a.insert(-9.0);
  a.insert(1.2);
  a.insert(3.3);
  a.insert(-0.3);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, mass[j++]);
  }
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 6);
};

TEST(multiset, insert) {
  s21::multiset<double> a({22.2, 3.3, -9.0});
  double mass[] = {-9., -0.3, 1.2, 3.3, 3.3, 22.2};
  int j = 0;
  a.insert(1.2);
  a.insert(3.3);
  a.insert(-0.3);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, mass[j++]);
  }
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 6);
};

TEST(multiset, erase_empty) {
  s21::multiset<double> a;
  EXPECT_THROW(a.erase(nullptr), std::out_of_range);
};

TEST(multiset, erase1) {
  s21::multiset<std::string> a({"Hello", "world", "and", "humanty"});
  s21::multiset<std::string> b({"Life"});
  auto rem = b.begin();
  a.erase(rem);
  EXPECT_EQ(a.size(), 4);
};

TEST(multiset, erase2) {
  s21::multiset<std::string> a({"Hello", "world", "and", "humanity"});
  const char* mass[] = {"Hello", "and", "humanity", "world"};
  int j = 0;
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, mass[j++]);
  }
  for (int i = 0; i < 4; ++i) {
    auto rem = a.begin();
    a.erase(rem);
    int k = i + 1;
    if (i != 3) {
      for (auto j = a.begin(); j != a.end(); ++j) {
        EXPECT_EQ(*j, mass[k++]);
      }
    } else {
      EXPECT_EQ(a.empty(), true);
      EXPECT_EQ(a.size(), 0);
    }
  }
};

TEST(multiset, swap) {
  s21::multiset<std::string> a({"1", "2", "3", "4"}), b({"5", "6", "7"});
  const char* mass1[] = {"1", "2", "3", "4"};
  const char* mass2[] = {"5", "6", "7"};
  std::swap(a, b);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 4);
  int j = 0;
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass2[j++], *i);
  }
  j = 0;
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(mass1[j++], *i);
  }
};

TEST(multiset, empty_swap) {
  s21::multiset<int> a, b;
  std::swap(a, b);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
};

TEST(multiset, merge1) {
  s21::multiset<int> a, b({1, 2, 3, 4, 5});
  int mass[] = {1, 2, 3, 4, 5}, j = 0;
  a.merge(b);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(b.empty(), true);
  EXPECT_EQ(b.size(), 0);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass[j++], *i);
  }
};

TEST(multiset, merge2) {
  s21::multiset<int> a, b({1, 2, 3, 4, 4, 5});
  int mass[] = {1, 2, 3, 4, 4, 5}, j = 0;
  a.merge(b);
  EXPECT_EQ(a.size(), 6);
  EXPECT_EQ(b.empty(), true);
  EXPECT_EQ(b.size(), 0);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass[j++], *i);
  }
};

TEST(multiset, merge3) {
  s21::multiset<double> a({3., 12., 45., 50., 64., 75., 80.});
  s21::multiset<double> b({1., 12., 13., 15., 50., 70., 80.});
  double mass1[] = {1.,  3.,  12., 12., 13., 15., 45.,
                    50., 50., 64., 70., 75., 80., 80.};
  a.merge(b);
  int j = 0;
  EXPECT_EQ(a.size(), 14);
  EXPECT_EQ(b.size(), 0);
  EXPECT_EQ(b.empty(), true);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass1[j++], *i);
  }
};

TEST(multiset, counter1) {
  s21::multiset<int> a({1, 2, 3, 4, 5, 4});
  EXPECT_EQ(a.count(50), 0);
  EXPECT_EQ(a.count(4), 2);
  EXPECT_EQ(a.count(1), 1);
};

TEST(multiset, counter2) {
  s21::multiset<int> a;
  EXPECT_EQ(a.count(50), 0);
};

TEST(multiset, find_contains_1) {
  s21::multiset<int> a({1, 2, 3, 4, 5});
  auto iter = a.find(2);
  a.erase(iter);
  EXPECT_EQ(a.contains(2), false);
  iter = a.find(4);
  a.erase(iter);
  EXPECT_EQ(a.contains(4), false);
  iter = a.find(5);
  a.erase(iter);
  EXPECT_EQ(a.contains(5), false);
  iter = a.find(3);
  a.erase(iter);
  EXPECT_EQ(a.contains(3), false);
  iter = a.find(1);
  a.erase(iter);
  EXPECT_EQ(a.contains(1), false);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.find(10), a.end());
};

TEST(multiset, find_contains_2) {
  s21::multiset<double> a({-1.3, 2.2, 0.3, 4.3, 53.1});
  EXPECT_EQ(a.contains(2.2), true);
  auto iter = a.find(2.2);
  a.erase(iter);
  EXPECT_EQ(a.contains(2.2), false);
  EXPECT_EQ(a.contains(4.3), true);
  iter = a.find(4.3);
  a.erase(iter);
  EXPECT_EQ(a.contains(4.3), false);
  EXPECT_EQ(a.contains(53.1), true);
  iter = a.find(53.1);
  a.erase(iter);
  EXPECT_EQ(a.contains(53.1), false);
  EXPECT_EQ(a.contains(0.3), true);
  iter = a.find(0.3);
  a.erase(iter);
  EXPECT_EQ(a.contains(0.3), false);
  EXPECT_EQ(a.contains(-1.3), true);
  iter = a.find(-1.3);
  a.erase(iter);
  EXPECT_EQ(a.contains(-1.3), false);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.find(10), a.end());
};

TEST(multiset, find_contains_3) {
  s21::multiset<std::string> a({"a", "b", "c"});
  EXPECT_EQ(a.contains("a"), true);
  EXPECT_EQ(a.contains("j"), false);
  auto iter = a.find("a");
  a.erase(iter);
  iter = a.find("j");
  EXPECT_THROW(a.erase(iter), std::logic_error);
};

TEST(multiset, range) {
  s21::multiset<int> a({1, 2, 2, 3});
  auto res = a.equal_range(4);
  EXPECT_EQ(res.first, res.second);
  res = a.equal_range(2);
  EXPECT_EQ(a.lower_bound(2), res.first);
  EXPECT_EQ(a.lower_bound(3), res.second);
  for (auto i = res.first; i != res.second; ++i) {
    EXPECT_EQ(*i, 2);
  }
  res = a.equal_range(1);
  EXPECT_EQ(res.first, a.begin());
  EXPECT_EQ(res.second, a.lower_bound(2));
  res = a.equal_range(3);
  EXPECT_EQ(res.first, a.end_elem());
  EXPECT_EQ(res.second, a.end());
};

TEST(multiset, lower_upper_bound) {
  s21::multiset<int> a({1, 2, 2, 2, 3});
  EXPECT_EQ(a.lower_bound(1), a.begin());
  EXPECT_EQ(a.upper_bound(1), a.lower_bound(2));
  EXPECT_EQ(a.upper_bound(2), a.lower_bound(3));
  EXPECT_EQ(a.upper_bound(3), a.end());
};

TEST(multiset, insert_many_1) {
  s21::multiset<int> s;
  int a[] = {1, 2, 3, 8, 4, 5, 6, 7, 8}, b[] = {1, 2, 3, 4, 5, 6, 7, 8};
  auto vec = s.insert_many(1.1, 2.4f, 3, 8, std::move(4), 5, 6.6, 7.f, 8);
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(a[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, b[j++]);
  }
};

TEST(multiset, insert_many_2) {
  s21::multiset<int> s;
  auto vec = s.insert_many();
  int j = 0;
  EXPECT_EQ(vec.empty(), true);
  EXPECT_EQ(s.empty(), true);
};

TEST(multiset, insert_many_3) {
  s21::multiset<int> s({10, 12, 14});
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14};
  auto vec = s.insert_many(1.1, 2.4f, 3, std::move(4), 5, 6.6, 7.f, 8);
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(a[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};

TEST(multiset, insert_many_4) {
  s21::multiset<double> s;
  double a[] = {1.1, 2.4, 3, 4, 5, 6.6, 7., 8};
  auto vec = s.insert_many(1.1, 2.4, 3, std::move(4), 5, 6.6, 7.f, 8);
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(a[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};

TEST(multiset, insert_many_5) {
  s21::multiset<int> s;
  auto vec = s.insert_many();
  int j = 0;
  EXPECT_EQ(vec.empty(), true);
  EXPECT_EQ(s.empty(), true);
};

TEST(multiset, insert_many_6) {
  s21::multiset<double> s({10.2, 12.1, 14.8});
  double a[] = {-1.1, 2.4, 3, 4, 5, 6.6, 7, 8, 10.2, 12.1, 14.8};
  auto vec = s.insert_many(-1.1, 2.4, 3, std::move(4), 5, 6.6, 7.f, 8);
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(a[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};

TEST(multiset, insert_many_7) {
  s21::multiset<std::string> s;
  std::string a[] = {"a", "b", "c", "d", "d"}, b[] = {"c", "a", "d", "d", "b"};
  auto vec = s.insert_many("c", "a", "d", std::move("d"), "b");
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(b[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};

TEST(multiset, insert_many_8) {
  s21::multiset<std::string> s;
  auto vec = s.insert_many();
  int j = 0;
  EXPECT_EQ(vec.empty(), true);
  EXPECT_EQ(s.empty(), true);
};

TEST(multiset, insert_many_9) {
  s21::multiset<std::string> s({"h", "w", "z"});
  std::string a[] = {"a", "b", "c", "h", "w", "z"}, b[] = {"c", "b", "a"};
  auto vec = s.insert_many(std::move("c"), std::move("b"), "a");
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(b[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};