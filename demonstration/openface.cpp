#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>	
using namespace std;
using namespace cv;


class VideoProcesser {
	char* inputfilename;
	bool is_digit(char a) {
		if (a >= '0' && a <= '9')
			return true;
		else
			return false;
	}
	double extract_double_from_string(string s) {
		double x = 0;
		int i = 0;
		while (i < s.length() && is_digit(s[i])) {
			x *= 10;
			x += s[i] - '0';
			++i;
		}
		if (s[i] != '.') {
			cout << "NOOOOOOO";
			return -1000000.0;
		}
		++i;
		double d = 10.0;
		while (i < s.length() && is_digit(s[i])) {
			double a = s[i] - '0';
			x += a / d;
			d *= 10;
			++i;
		}
		return x;
	}
	int extract_int_from_string(string s) {
		int x = 0;
		int i = 0;
		while (i < s.length() && is_digit(s[i])) {
			x *= 10;
			x += s[i] - '0';
			++i;
		}
		return x;
	}

	pair<vector<double>, vector<double> > get_eye_marks_from_photo() {
		vector<string> v;
		string s;
		freopen("image_5.csv", "r", stdin);
		while (!feof(stdin)) {
			cin >> s;
			v.push_back(s);
		}
		cout << v.size() << endl;
		cout << v[711] << endl;
		vector<double> eye_marks_x(56), eye_marks_y(56);
		vector<vector<string> > eye_marks_strings(56, vector<string>(2));
		for (int i = 0; i < 56; ++i) {
			eye_marks_strings[i][0] = v[10 + i + v.size() / 2];
		}
		for (int i = 0; i < 56; ++i) {
			eye_marks_strings[i][1] = v[66 + i + v.size() / 2];
		}
		for (int i = 0; i < 56; ++i) {
			eye_marks_x[i] = extract_double_from_string(eye_marks_strings[i][0]);
			eye_marks_y[i] = extract_double_from_string(eye_marks_strings[i][1]);
		}
		return make_pair(eye_marks_x, eye_marks_y);
	}

	pair<pair<vector<vector<double> >, vector<vector<double> > >, pair<vector<int>, vector<double> > > get_eye_marks_from_video() {
		vector<string> v;
		string s;
		freopen(inputfilename, "r", stdin);
		int j = 0, k = 0;
		char c;
		while (!feof(stdin)) {
			cin >> s;
			v.push_back(s);
			++j;
		}
		//cout << j << endl;
		//cout << v[713] << endl;
		int sz = v.size() / 714 - 1;
		vector< vector<double> > eye_marks_x(sz, vector<double>(56)), eye_marks_y(sz, vector<double>(56));
		vector<double> time_stamps(sz);
		vector<int> frames(sz);
		vector<vector<string> > eye_marks_strings1(sz, vector<string>(56)), eye_marks_strings2(sz, vector<string>(56));
		vector<string> time_stamps_strings(sz);
		vector<string> frames_strings(sz);
		for (int j = 0; j < sz; ++j) {
			for (int i = 0; i < 56; ++i) {
				eye_marks_strings1[j][i] = v[(j + 1) * 714 + 13 + i];
				eye_marks_strings2[j][i] = v[69 + i + (j + 1) * 714];
			}
			time_stamps_strings[j] = v[(j + 1) * 714 + 2];
			frames_strings[j] = v[(j + 1) * 714];
		}
		for (int j = 0; j < sz; ++j) {
			for (int i = 0; i < 56; ++i) {
				eye_marks_x[j][i] = extract_double_from_string(eye_marks_strings1[j][i]);
				eye_marks_y[j][i] = extract_double_from_string(eye_marks_strings2[j][i]);
			}
			time_stamps[j] = extract_double_from_string(time_stamps_strings[j]);
			frames[j] = extract_int_from_string(frames_strings[j]);
		}
		return make_pair(make_pair(eye_marks_x, eye_marks_y), make_pair(frames, time_stamps));
	}

	double extract_center_marks_from_frame(vector<double> eye_marks, int num) {
		vector<double> sight_marks_1(8), sight_marks_2(8);
		vector<double> big_circle_marks_1(8), big_circle_marks_2(8);
		for (int i = 0; i < 8; ++i) {
			sight_marks_1[i] = eye_marks[i + 20];
			sight_marks_2[i] = eye_marks[i + 48];
			big_circle_marks_1[i] = eye_marks[i];
			big_circle_marks_2[i] = eye_marks[i + 28];
		}
		vector<double>x(4, 0);
		for (int i = 0; i < 8; ++i) {
			x[0] += sight_marks_1[i];
			x[1] += sight_marks_2[i];
			x[2] += big_circle_marks_1[i];
			x[3] += big_circle_marks_2[i];
		}
		x[0] /= 8;
		x[1] /= 8;
		x[2] /= 8;
		x[3] /= 8;
		return x[num];
	}
	vector<double> extract_center_marks_from_video(vector<vector<double> > eye_marks, int num) {
		int sz = eye_marks.size(), n = eye_marks[0].size();
		vector<double> x(sz);
		for (int j = 0; j < sz; ++j) {
			x[j] = extract_center_marks_from_frame(eye_marks[j], num);
		}
		return x;
	}

	//���������� �� �������
	vector<pair<double, double> > extract_key_points_from_video(vector<double> x, vector<double> y, vector<double> t, double left_border = 0, double right_border = 0, double delta = 0) {
		int n = t.size();
		vector<pair<double, int> > num_t(n);
		for (int i = 0; i < n; ++i) {
			num_t[i] = make_pair(t[i], i);
		}
		sort(num_t.begin(), num_t.end());

		vector<double> sorted_x(n), sorted_y(n);
		for (int i = 0; i < n; ++i) {
			sorted_x[i] = x[num_t[i].second];
			sorted_y[i] = y[num_t[i].second];
		}
		vector<double> starts(4), ends(4);
		int main_start, main_end;
		double main_start_t, main_end_t;
		int i1 = 0, i2 = n - 1;
		while (i1 < n && num_t[i1].first < num_t[0].first + left_border)
			++i1;
		while (i2 >= 0 && num_t[i2].first >= num_t[n - 1].first - right_border)
			--i2;
		main_end = i2;
		main_start = i1;
		main_start_t = num_t[i1].first;
		main_end_t = num_t[i2].first;
		starts[0] = main_start_t;
		starts[2] = (main_start_t + main_end_t) / 2;
		starts[1] = (main_start_t + starts[2]) / 2;
		starts[3] = (starts[2] + main_end_t) / 2;
		ends[0] = starts[1];
		ends[1] = starts[2];
		ends[2] = starts[3];
		ends[3] = main_end_t;
		for (int i = 0; i < 4; ++i) {
			ends[i] -= delta;
			starts[i] += delta;
		}
		if (i1 >= n || i2 < 0 || i2 <= i1) {
			cout << "TIME_ERROR!!!!!!";
		}
		vector<int> frame_nums(4, 0);
		vector<pair<double, double> > ans(4, make_pair(0.0, 0.0));
		for (int i = 0; i < n; ++i) {
			double tt = num_t[i].first;
			for (int j = 0; j < 4; ++j) {
				if (tt >= starts[j] && tt < ends[j]) {
					ans[j].first += sorted_x[i];
					ans[j].second += sorted_y[i];
					++frame_nums[i];
				}
			}
		}
		for (int i = 0; i < 4; ++i) {
			ans[i].first /= frame_nums[i];
			ans[i].second /= frame_nums[i];
		}
		return ans;
	}

	Mat build_transformation_matrix(vector<double> end_vec_x, vector<double> end_vec_y) {
		vector<Point2f> end_vec_point(4);
		for (int i = 0; i < 4; ++i) {
			end_vec_point[i] = Point2f(end_vec_x[i], end_vec_y[i]);
		}

		Point2f A_(0, 0), B_(0, 1), C_(1, 1), D_(1, 0);
		vector<Point2f> start_vec_point_2f(4);
		start_vec_point_2f[0] = A_;
		start_vec_point_2f[1] = B_;
		start_vec_point_2f[2] = C_;
		start_vec_point_2f[3] = D_;

		return getPerspectiveTransform(start_vec_point_2f, end_vec_point);
	}

	pair<vector<double>, vector<double> > get_stimul_eye_screen_coordinates(vector<double> x, vector<double> y, Mat transform_matrix) {
		int n = x.size();
		vector<Point2f> start_Points(n);
		for (int i = 0; i < n; ++i) {
			start_Points[i] = Point2f(x[i], y[i]);
		}
		vector<Point2f> result_Points = start_Points;
		perspectiveTransform(start_Points, result_Points, transform_matrix);
		vector<double> x_(n), y_(n);
		for (int i = 0; i < n; ++i) {
			x_[i] = result_Points[i].x;
			y_[i] = result_Points[i].y;
		}
		return make_pair(x_, y_);
	}
public:
	VideoProcesser(char* in = "Nikita.csv") {
		inputfilename = in;
	}
	pair<vector<double>, vector<double> > solve(double callibration_time = 20.0) {
		pair<pair<vector<vector<double> >, vector<vector<double> > >, pair<vector<int>, vector<double> > > eye_marks_v = get_eye_marks_from_video();
		vector<double> eye_x_coordinates = extract_center_marks_from_video(eye_marks_v.first.first, 0), eye_y_coordinates = extract_center_marks_from_video(eye_marks_v.first.second, 0);
		vector<double> t = eye_marks_v.second.second;
		vector<pair<double, double> > callibration_points = extract_key_points_from_video(eye_x_coordinates, eye_y_coordinates, t, 0.0, 40.0, 0.0);
		vector<double> callib_point_x(4), callib_point_y(4);
		for (int i = 0; i < 4; i++) {
			callib_point_x[i] = callibration_points[i].first;
			callib_point_y[i] = callibration_points[i].second;
		}
		int i1 = 0;
		vector<double> stimul_eye_marks_x, stimul_eye_marks_y;
		while (i1 < t.size() && t[i1] < callibration_time)
			++i1;
		while (i1 < t.size()) {
			stimul_eye_marks_x.push_back(eye_x_coordinates[i1]);
			stimul_eye_marks_y.push_back(eye_y_coordinates[i1]);
			++i1;
		}
		Mat perspective_mat = build_transformation_matrix(callib_point_x, callib_point_y);
		pair<vector<double>, vector<double> > ans = get_stimul_eye_screen_coordinates(stimul_eye_marks_x, stimul_eye_marks_y, perspective_mat);
		return ans;
	}
};

//int main() {
//	char input_file_name[11] = "Nikita.csv";
//	VideoProcesser v(input_file_name);
//	pair<vector<double>, vector<double> > ans = v.solve();
//	//ans.first - �-���������� ��������� �������
//	//ans.second - y-���������� ��������� ������� 
//	waitKey(0);
//	return 0;
//}
