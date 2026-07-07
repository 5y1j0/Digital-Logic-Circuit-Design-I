#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_BITS = 100;

// 배열에 특정한 값이 있는지 확인하는 함수
bool inarray(string arr[], int count, string value) {
	for (int i = 0; i < count; i++) {
		if (arr[i] == value)
			return true;
	}
	return false;
}

// Implicant가 특정한 minterm을 커버하는지 체크하는 함수
bool covers(string implicant, string minterm) {
	for (int i = 0; i < implicant.length(); i++) {
		if (implicant[i] == '-')
			continue;
		if (implicant[i] != minterm[i])
			return false;
	}
	return true;
}
// 입력 파일을 읽는 함수
void readinputfile(string filename) {
	ifstream inputfile(filename);
	if (!inputfile) {
		cout << "입력 파일을 열 수 없습니다." << endl; // 입력 파일이 안열릴 경우 오류 메시지 출력
		return;
	}

	int bit_length;
	inputfile >> bit_length; // 파일의 첫번째 줄에서 비트 길이를 읽음

	string terms[100]; // 모든 용어를 저장할 배열
	string true_minterms[100]; // m으로 시작하는 true minterm만 저장할 배열
	int term_count = 0, true_count = 0;

	string line;
	while (getline(inputfile, line)) { // 파일에서 한 줄씩 읽기
		if (line.empty())
			continue; // 비어있는 줄은 건너뛰기
		if (line[0] == 'm') {
			string term = line.substr(2); // m으로 시작하는 줄을 저장
			true_minterms[true_count++] = term;
			terms[term_count++] = term;
		}
		else if (line[0] == 'd') {
			terms[term_count++] = line.substr(2); // d로 시작하는 줄을 저장
		}
	}
	inputfile.close(); // 파일 닫기

	// 1개수 그룹핑
	string groups[MAX_BITS + 1][100]; // 1의 개수에 따라 minterm들을 그룹화하는 배열
	int group_count[MAX_BITS + 1] = { 0 }; // 각 그룹에 속하는 항의 개수를 저장

	for (int i = 0; i < term_count; i++) {
		int one_count = 0;
		for (char c : terms[i])
			if (c == '1')
				one_count++; // 각 항에서 1의 개수 세기
		groups[one_count][group_count[one_count]++] = terms[i]; // 1의 개수에 맞게 그룹에 배치
	}
	// 퀸_맥클러스키 알고리즘으로 항들을 묶어가기
	string primeimplicants[500]; // prime implicant를 저장할 배열
	int primecount = 0; // prime implicant의 개수
	bool can_merge = true; // 더이상 묶을 수 있는 것들이 있는지 체크하는 변수

	while (can_merge) { // 묶을 수 있는 항이 있으면 계속 반복
		can_merge = false;
		bool is_merged[MAX_BITS + 1][100] = { false }; // 항이 묶였는지 체크
		string newgroups[MAX_BITS + 1][100]; // 새 그룹들
		int newgroupscount[MAX_BITS + 1] = { 0 }; // 새 그룹의 항 개수
		
		for (int i = 0; i < MAX_BITS; i++) {
			for (int j = 0; j < group_count[i]; j++) {
				for (int k = 0; k < group_count[i + 1]; k++) {
					int diffcount = 0;
					string t1 = groups[i][j], t2 = groups[i + 1][k];
					for (int b = 0; b < bit_length; b++)
						if (t1[b] != t2[b]) diffcount++; // 두 항의 차이 개수 세기
					if (diffcount == 1) { // 두 항의 차이가 1이면 묶을 수 있음
						string merged = "";
						for (int b = 0; b < bit_length; b++)
							merged += (t1[b] == t2[b]) ? t1[b] : '-'; // 차이 나는 비트는 '-'로 변경
						if (!inarray(newgroups[i], newgroupscount[i], merged))
							newgroups[i][newgroupscount[i]++] = merged; // 새로 만든 항을 새 그룹에 추가
						is_merged[i][j] = true;
						is_merged[i + 1][k] = true;
						can_merge = true;
					}
				}
			}
		}
		// 묵이지 않은 항 저장
		for (int i = 0; i <= MAX_BITS; i++) {
			for (int j = 0; j < group_count[i]; j++) {
				if (!is_merged[i][j]) {
					string term = groups[i][j];
					if (!inarray(primeimplicants, primecount, term)) {
						primeimplicants[primecount++] = term; // 묶이지 않은 항은 prime implicant에 추가
					}
				}
			}
		}
		// 그룹 갱신
		for (int i = 0; i < MAX_BITS; i++) {
			group_count[i] = newgroupscount[i]; // 새 그룹의 개수로 업데이트
			for (int j = 0; j < group_count[i]; j++)
				groups[i][j] = newgroups[i][j]; // 새 그룹으로 업데이트
		}
	}
	// prime implicant table 만들기
	bool table[500][100] = { false }; // prime implicant와 minterm의 관계를 저장하는 table
	for (int i = 0; i < primecount; i++) {
		for (int j = 0; j < true_count; j++) {
			if (covers(primeimplicants[i], true_minterms[j])) {
				table[i][j] = true; // 해당 prime implicant가 해당 minterm을 커버하면 true로 표시
			}
		}
	}
	// essential prime implicant 추출
	bool used[500] = { false }; // 사용된 prime implicant를 체크하는 배열
	ofstream outputfile("result.txt"); // 결과 파일을 열기
	if (!outputfile) {
		cout << "결과 파일을 열 수 없습니다." << endl; // 결과 피일이 안열릴 경우 오류 메시지 출력
		return;
	}
	for (int j = 0; j < true_count; j++) { // 각 minterm에 대해서 essential prime implicant를 찾기
		int count = 0;
		int epiIndex = -1;
		for (int i = 0; i < primecount; i++) {
			if (table[i][j]) {
				count++;
				epiIndex = i;
			}
		}
		if (count == 1 && !used[epiIndex]) { // 하나의 prime implicant만 해당 minterm을 커버하면 이를 essential prime implicant로 판단
			outputfile << primeimplicants[epiIndex] << endl;
			used[epiIndex] = true; // 해당 prime implicant는 사용되었으므로 체크
		}
	}
	// essential prime implicant가 커버한 minterm 확인 및 커버되지 않은 minterm을 커버할 다른 prime implicant 찾기
	bool minterm_covered[100] = { false }; // minterm이 커버되었는지 여부 확인
	for (int j = 0; j < true_count; j++) {
		for (int i = 0; i < primecount; i++) {
			if (used[i] && table[i][j]) {
				minterm_covered[j] = true; // essential prime implicant가 minterm을 커버한 경우
				break;
			}
		}
	}
	// essential prime implicant가 커버하지 못한 minterm들이 있는 동안 반복
	while (true) {
		int uncovered_count = 0;
		for (int j = 0; j < true_count; j++) {
			if (!minterm_covered[j]) uncovered_count++;
		}
		if (uncovered_count == 0)
			break; // 모두 다 커버되었으면 끝

		// 남은 minterm들을 가장 많이 커버하는 prime implicant 찾기
		int best_primeimplicant = -1;
		int best_cover = -1;

		for (int i = 0; i < primecount; i++) {
			if (used[i])
				continue;

			int cover_count = 0;
			for (int j = 0; j < true_count; j++) {
				if (!minterm_covered[j] && table[i][j]) {
					cover_count++;
				}
			}
			if (cover_count > best_cover) {
				best_cover = cover_count;
				best_primeimplicant = i;
			}
		}
		// 가장 좋은 PI 선택해서 추가
		if (best_primeimplicant != -1) {
			outputfile << primeimplicants[best_primeimplicant] << endl;
			used[best_primeimplicant] = true;

			for (int j = 0; j < true_count; j++) {
				if (table[best_primeimplicant][j]) {
					minterm_covered[j] = true;
				}
			}
		}
		else {
			break; // 더 이상 커버할 prime implicant가 없음
		}
	}

	outputfile.close();

	// 트랜지스터 수 계산
	bool notused[MAX_BITS] = { false };
	int total_transistor = 0;
	int AND_transistor = 0;
	int OR_transistor = 0;
	int NOT_transistor = 0;
	int essential_count = 0;

	for (int i = 0; i < primecount; i++) {
		if (used[i]) {
			essential_count++;

		// Not 게이트 트랜지스터 수 계산
			for (int j = 0; j < bit_length; j++) {
				if (primeimplicants[i][j] == '0' && !notused[j]) {
					notused[j] = true;
					NOT_transistor += 2;
				}
			}
			//And 게이트 트랜지스터 수 계산
			int count01 = 0;
			for (int j = 0; j < bit_length; j++) {
				if (primeimplicants[i][j] != '-') {
					count01++;
				}
			}
			int ANDgate_cost = 2 * count01 + 2;
			AND_transistor += ANDgate_cost;
		}
	}
	// OR 게이트 트랜지스터 수 계산
	OR_transistor = 2 * essential_count + 2;
	// 총 트랜지스터 수 계산
	total_transistor = NOT_transistor + AND_transistor + OR_transistor;
	// 결과 출력
	ofstream fout("result.txt", ios::app);
	fout << endl << "Cost (# of transistors): " << total_transistor << endl;
	fout.close();
}

int main() {
	string filename = "input_minterm.txt";
	readinputfile(filename); // 입력 파일 처리 함수 호출
	return 0;
}