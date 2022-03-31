#include <iostream>
using namespace std;
int main() {
    while (true){
        string fileName;
        char filter;
        cout << "Ahlan ya user ya habibi " << char(1) << endl;
       cout <<"Please enter file name of the image to process : " << endl << "->";
       cin >> fileName;
       cout << "Please select a filter to apply or 0 to exit:\n";
       cout << "1-Black & white Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Image\n5-Darken and Lighten Image";
       cout << "\n6- Rotate Image\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink Image\na- Mirror 1/2 Image";
       cout << "\nb- Shuffle Image\nc- Blur Image\ns- Save the image to a file\n0- Exit\n-->";
       cin >> filter;
        if (filter =='0'){
           break;
       }

    }
    return 0;
}
