#include<iostream>
#include<vector>

using namespace std;

class Signal {
public:
	vector<int> sampleValues;
	vector<int> indexSequence;
	int samplingFrequency;
	
	// Constructor
	Signal(int numberOfValue, int Hz) {
		// Nhap vao day gia tri
		cout << "Type sample values: ";
		for (int i = 0; i < numberOfValue; i++) {
			int x; cin >> x;
			sampleValues.push_back(x);
		}
		
		// Nhap vao day chi so
		cout << "Type start index: ";
		int x; cin >> x; indexSequence.push_back(x);
		for (int i = 1; i < numberOfValue; i++) {
			x++;
			indexSequence.push_back(x);
		}
		
		// Tan so lay mau
		samplingFrequency = Hz;
		
		// In ra day gia tri, day chi so va tan so lay mau
		cout << endl << "Signal: ";
		for (int i : sampleValues) cout << i << " ";
		cout << endl << "        ";
		for (int i : indexSequence) cout << i << " ";
		cout << endl << "Sampling Frequency: " << samplingFrequency << " Hz." << endl << endl;
	}
	
	// 1.Dich thoi gian
	void Time_Shifting(int m) {
		for (int i = 0; i < indexSequence.size(); i++) indexSequence[i] += m;
		cout << "Time shifting: x[n] -> x[n - " << m <<"]" << endl;
		cout << "Output signal: ";
		for (int i : sampleValues) cout << i << " ";
		cout << endl << "               ";
		for (int i : indexSequence) cout << i << " ";
		cout << endl << "----------------------------------------------------------------------------";
		cout << endl << endl;
	}
	
	// 2.Dao nguoc thoi gian
	void Time_Reversal() {
		for (int i = 0; i < indexSequence.size(); i++) indexSequence[i] *= -1;
		cout << "Time reversal:" << endl;
		cout << "Output signal: ";
		for (int  i = sampleValues.size() - 1; i >= 0; i--) cout << sampleValues[i] << " ";
		cout << endl << "               ";
		for (int  i = indexSequence.size() - 1; i >= 0; i--) cout << indexSequence[i] << " ";
		cout << endl << "----------------------------------------------------------------------------";
		cout << endl << endl;
	}
	
	// 3.Giam tan so lay mau
	void Downsampling(int M) {
		vector<int> newSampleValues;
		vector<int> newIndexSequence;
		for (int i = 0; i < sampleValues.size(); i += M) {
			newSampleValues.push_back(sampleValues[i]);
			newIndexSequence.push_back(indexSequence[i]);
		}
		cout << "Downsampling by a factor of " << M << ":" << endl;
		cout << "Output signal: ";
		for (int i : newSampleValues) cout << i << " ";
		cout << endl << "               ";
		for (int i : newIndexSequence) cout << i << " ";
		cout << endl << "----------------------------------------------------------------------------";
		cout << endl << endl;
	}
	
	// 4.Tang tan so lay mau
	void Upsampling(int L) {
		vector<int> newSampleValues;
		vector<int> newIndexSequence;
		for (int i = 0, j = indexSequence[0]; i < sampleValues.size() - 1; i++, j++) {
			newSampleValues.push_back(sampleValues[i]);
			newIndexSequence.push_back(j);
			int a = (sampleValues[i + 1] - sampleValues[i]) / L;
			
			// Noi suy L - 1 mau
			for (int k = 0; k < L - 1; k++) {
				j++;
				newIndexSequence.push_back(j);
				newSampleValues.push_back(newSampleValues[newSampleValues.size() - 1] + a);
			}
		}
		newSampleValues.push_back(sampleValues[sampleValues.size() - 1]);
		newIndexSequence.push_back(newIndexSequence[newIndexSequence.size() - 1] + 1);
		
		cout << "Upsampling by a factor of " << L << ":" << endl;
		cout << "Output signal: ";
		for (int i : newSampleValues) cout << i << " ";
		cout << endl << "               ";
		for (int i : newIndexSequence) cout << i << " ";
		cout << endl << "----------------------------------------------------------------------------";
		cout << endl << endl;
	}
};

int main() {
	bool runningProgram = true;
	while (runningProgram) {
		cout << "Type the number of value: ";
		int a; cin >> a;
		cout << "Type the sampling frequency: ";
		int b; cin >> b;
		Signal signal(a, b);
		
		cout << "1. Time Shifting" << endl;
		cout << "2. Time Reversal" << endl;
		cout << "3. Downsampling" << endl;
		cout << "4. Upsampling" << endl;
		cout << "5. Computing the sum" << endl;
		cout << "6. Computing the product" << endl;
		cout << "7. Quit" << endl;
		cout << "Select the request: ";
		int yourSelection; cin >> yourSelection;
		cout << endl;
		
		if (yourSelection == 1) {
			cout << "Type delay: ";
			int m; cin >> m;
			signal.Time_Shifting(m);
		}
		
		else if (yourSelection == 2) {
			signal.Time_Reversal();
		}
		
		else if (yourSelection == 3) {
			cout << "Type coefficient: ";
			int M; cin >> M;
			signal.Downsampling(M);
		}

		else if (yourSelection == 4) {
			cout << "Type coefficient: ";
			int L; cin >> L;
			signal.Upsampling(L);
		}
		
		else if (yourSelection == 5) {
			cout << "- Type the second signal" << endl << "Type the number of value: ";
			int c; cin >> c;
			cout << "Type the sampling frequency: ";
			int d; cin >> d;
			Signal signal_2(c, d);
			
			int min1 = signal.indexSequence[0], max1 = signal.indexSequence[a - 1]; //min index va max index cua tin hieu 1
			int min2 = signal_2.indexSequence[0], max2 = signal_2.indexSequence[c - 1]; //min index va max index cua tin hieu 2
			int minIndex = min(min1, min2), maxIndex = max(max1, max2);
			int n = maxIndex - minIndex + 1;
			vector<int> result_sampleValues(n);
			vector<int> result_indexSequence(n);
			vector<int> new_sampleValues_1;
			vector<int> new_indexSequence_1;
			vector<int> new_sampleValues_2;
			vector<int> new_indexSequence_2;
			
			int h = min1, k = max1;
			while (h > minIndex) {
			    new_sampleValues_1.push_back(0);
				new_indexSequence_1.push_back(min1 - h + minIndex);
				h--;
			}
			for (int x : signal.sampleValues) new_sampleValues_1.push_back(x);
			for (int x : signal.indexSequence) new_indexSequence_1.push_back(x);
			while (k < maxIndex) {
				new_sampleValues_1.push_back(0);
				new_indexSequence_1.push_back(++k);
			}
			
			int u = min2, v = max2;
			while (u > minIndex) {
			    new_sampleValues_2.push_back(0);
				new_indexSequence_2.push_back(min2 - u + minIndex);
				u--;
			}
			for (int x : signal_2.sampleValues) new_sampleValues_2.push_back(x);
			for (int x : signal_2.indexSequence) new_indexSequence_2.push_back(x);
			while (v < maxIndex) {
				new_sampleValues_2.push_back(0);
				new_indexSequence_2.push_back(++v);
			}
			
			for (int i = 0; i < n; i++) {
				result_sampleValues[i] = new_sampleValues_1[i] + new_sampleValues_2[i]; 
			}
			result_indexSequence[0] = minIndex;
			for (int i = 1; i < n; i++) {
				result_indexSequence[i] = result_indexSequence[i - 1] + 1;
			}
			
			cout << "Output signal: ";
			for (int i : result_sampleValues) cout << i << " ";
			cout << endl << "               ";
			for (int i : result_indexSequence) cout << i << " ";
			cout << endl << "----------------------------------------------------------------------------";
			cout << endl << endl;
		}
		
		else if (yourSelection == 6) {
			cout << "1. Multiply by a constant" << endl;
			cout << "2. Multiply by another signal" << endl;
			cout << "Select the request: ";
			int selection; cin >> selection;
			cout << endl;
			
			if (selection == 1) {
				cout << "Type the constant: ";
				int z; cin >> z;
				for (int i = 0; i < a; i++) signal.sampleValues[i] *= z;
				cout << "Output signal: ";
				for (int i : signal.sampleValues) cout << i << " ";
				cout << endl << "               ";
				for (int i : signal.indexSequence) cout << i << " ";
				cout << endl << "----------------------------------------------------------------------------";
				cout << endl << endl;
			}
			
			else if (selection == 2) {
				cout << "- Type the second signal" << endl << "Type the number of value: ";
				int c; cin >> c;
				cout << "Type the sampling frequency: ";
				int d; cin >> d;
				Signal signal_2(c, d);
				
				int min1 = signal.indexSequence[0], max1 = signal.indexSequence[a - 1]; //min index va max index cua tin hieu 1
				int min2 = signal_2.indexSequence[0], max2 = signal_2.indexSequence[c - 1]; //min index va max index cua tin hieu 2
				int minIndex = min(min1, min2), maxIndex = max(max1, max2);
				int n = maxIndex - minIndex + 1;
				vector<int> result_sampleValues(n);
				vector<int> result_indexSequence(n);
				vector<int> new_sampleValues_1;
				vector<int> new_indexSequence_1;
				vector<int> new_sampleValues_2;
				vector<int> new_indexSequence_2;
				
				int h = min1, k = max1;
				while (h > minIndex) {
				    new_sampleValues_1.push_back(0);
					new_indexSequence_1.push_back(min1 - h + minIndex);
					h--;
				}
				for (int x : signal.sampleValues) new_sampleValues_1.push_back(x);
				for (int x : signal.indexSequence) new_indexSequence_1.push_back(x);
				while (k < maxIndex) {
					new_sampleValues_1.push_back(0);
					new_indexSequence_1.push_back(++k);
				}
				
				int u = min2, v = max2;
				while (u > minIndex) {
				    new_sampleValues_2.push_back(0);
					new_indexSequence_2.push_back(min2 - u + minIndex);
					u--;
				}
				for (int x : signal_2.sampleValues) new_sampleValues_2.push_back(x);
				for (int x : signal_2.indexSequence) new_indexSequence_2.push_back(x);
				while (v < maxIndex) {
					new_sampleValues_2.push_back(0);
					new_indexSequence_2.push_back(++v);
				}
				
				for (int i = 0; i < n; i++) {
					result_sampleValues[i] = new_sampleValues_1[i] * new_sampleValues_2[i]; 
				}
				result_indexSequence[0] = minIndex;
				for (int i = 1; i < n; i++) {
					result_indexSequence[i] = result_indexSequence[i - 1] + 1;
				}
				
				cout << "Output signal: ";
				for (int i : result_sampleValues) cout << i << " ";
				cout << endl << "               ";
				for (int i : result_indexSequence) cout << i << " ";
				cout << endl << "----------------------------------------------------------------------------";
				cout << endl << endl;
			}
		}
		
		else if (yourSelection == 7) {
			cout << "END PROGRAM!" << endl;
			runningProgram = false;
		}
	}
	
	return 0;
}
