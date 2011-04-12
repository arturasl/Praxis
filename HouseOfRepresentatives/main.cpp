#include      <algorithm>
#include      <cmath>
#include      <iomanip>
#include      <iostream>
#include      <list>
#include      <queue>
#include      <string>

using namespace std;

struct tStateData {
	int nItem;
	double fVal;
	int nRepresentatives;

	tStateData(int nItem = 0, double fVal = 0, int nRepresentatives = 0)
		: nItem(nItem), fVal(fVal), nRepresentatives(nRepresentatives) {
		;
	}

	friend bool operator <(const tStateData &lhs, const tStateData &rhs) {
		return lhs.fVal < rhs.fVal;
	}
};
int main() {
	const pair<string, int> aInitialData[] = {
		{"Alabama"        , 4779736}  , {"Alaska"         , 710231}
		, {"Arizona"        , 6392017}  , {"Arkansas"       , 2915918}  , {"California"    , 37253956}
		, {"Colorado"       , 5029196}  , {"Connecticut"    , 3574097}  , {"Delaware"      , 897934}
		, {"Florida"        , 18801310} , {"Georgia"        , 9687653}  , {"Hawaii"        , 1360301}
		, {"Idaho"          , 1567582}  , {"Illinois"       , 12830632} , {"Indiana"       , 6483802}
		, {"Iowa"           , 3046355}  , {"Kansas"         , 2853118}  , {"Kentucky"      , 4339367}
		, {"Louisiana"      , 4533372}  , {"Maine"          , 1328361}  , {"Maryland"      , 5773552}
		, {"Massachusetts"  , 6547629}  , {"Michigan"       , 9883640}  , {"Minnesota"     , 5303925}
		, {"Mississippi"    , 2967297}  , {"Missouri"       , 5988927}  , {"Montana"       , 989415}
		, {"Nebraska"       , 1826341}  , {"Nevada"         , 2700551}  , {"New Hampshire" , 1316470}
		, {"New Jersey"     , 8791894}  , {"New Mexico"     , 2059179}  , {"New York"      , 19378102}
		, {"North Carolina" , 9535483}  , {"North Dakota"   , 672591}   , {"Ohio"          , 11536504}
		, {"Oklahoma"       , 3751351}  , {"Oregon"         , 3831074}  , {"Pennsylvania"  , 12702379}
		, {"Rhode Island"   , 1052567}  , {"South Carolina" , 4625364}  , {"South Dakota"  , 814180}
		, {"Tennessee"      , 6346105}  , {"Texas"          , 25145561} , {"Utah"          , 2763885}
		, {"Vermont"        , 625741}   , {"Virginia"       , 8001024}  , {"Washington"    , 6724540}
		, {"West Virginia"  , 1852994}  , {"Wisconsin"      , 5686986}  , {"Wyoming"       , 563626}
	};

	priority_queue<tStateData> aQueue;
	tStateData tmpStateData;

	for (int i = 0; i != sizeof(aInitialData) / sizeof(pair<string, int>); ++i) {
		aQueue.push({i, aInitialData[i].second / sqrt(3), 1});
	}

	for (int i = 0; i < 385; ++i) {
		tmpStateData = aQueue.top();
		aQueue.pop();

		tmpStateData.nRepresentatives += 1;
		tmpStateData.fVal              = aInitialData[tmpStateData.nItem].second;
		tmpStateData.fVal             /= sqrt(tmpStateData.nRepresentatives * (tmpStateData.nRepresentatives + 1));

		aQueue.push(tmpStateData);
	}

	list<pair<string, int>> aResults;

	while (!aQueue.empty()) {
		tmpStateData = aQueue.top();
		aQueue.pop();
		aResults.push_back({aInitialData[tmpStateData.nItem].first, tmpStateData.nRepresentatives});
	}

	aResults.sort(
		[ ](const pair<string, int> &lhs, const pair<string, int> &rhs) {
			return lhs.second > rhs.second;
		}
	);

	for (auto it = aResults.begin(); it != aResults.end(); ++it) {
		cout << setw(20) << left << it->first << it->second << endl;
	}

	return 0;
}
