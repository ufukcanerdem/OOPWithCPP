/*
Ufukcan
Erdem
1901042686
*/
#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

const int MaximumColorValue=255;        //For RGB values, Maximum Value is 255.
enum Colors{Black=0,White=255};         //Colors enum class for values of White and Black.

class Pixel{                            //This class represent one pixel.
    private:
        int col1,col2,col3;             //col1=Red value of pixel, col2=Green Value of pixel, col3=Blue Value of pixel.
    public:
        int get_col1() const {          //Getters and setters for Pixel class.
            return col1;
        } 
        int get_col2() const {
            return col2;
        }
        int get_col3() const{
            return col3;
        }
        void set_col1(int _c) {
            col1=_c;
        }
        void set_col2(int _c) {
            col2=_c;
        }
        void set_col3(int _c) {
            col3=_c;
        }
        Pixel();
};

Pixel::Pixel() {                        //Default Constructor, All variables take '-1' value as their initial value for validity checking.
    col1=-1;     
    col2=-1;
    col3=-1;
}

class ppmImage{                             //ppmImage class.
    private:
        int width=0,length=0;               //Class private variables. Some of them has initial value for validity checking.
        string filename="default.ppm";
        vector< vector<Pixel> > ppmPixel;
    public:
        void createPixel(int _l, int _w);   //Pushs 'Pixel' elements into ppmPixel vector.
        void setLandW(int _l, int _w);      //Setter for length and width varibles.
        void setFilename(const string _fn); //Setter for filename variable.
        void setppmPixel(int index1, int index2, int _c1, int _c2, int _c3);    //Setter for one pixel of 'ppmPixel' vector (Changes individual pixel values).
        string getFilename () const {       //Getters of ppmImage class.
            return filename;
        }
        int getWidth() const {
            return width;
        }
        int getLength() const {
            return length;
        }
        vector<vector<Pixel>> getppmPixel() const {
            return ppmPixel;
        }
        bool check_validity();      //Checks validity of ppmImage class.
        void fill_white();          //Assigns the white value to ppmImage pixel's RGB values.
        void print_dimensions();    //Prints dimensions of ppmImage.
        void save_ppmimage() const; //Saves ppmImage to file.
        void save_ppmimage(const string _filename) const; //Saves ppmImage to specified '_filename'.
        void read_ppmimage(const string _filename); //Reads ppmImage(.ppm) file.
        void get_pixel_info(int _l, int _w, char _cp) const; //Returns information about the pixel's color.
        ppmImage();                         //Default Constuctor.
        ppmImage(const string _filename);   //Constructor takes a ppm file name as argument and creates object form file.
        ppmImage(const int _l, const int _w);   //Constructor which creates an object according to the given dimensions.
        ppmImage(const ppmImage& _ppmImage);    //Copy Constructor.
        ~ppmImage();    //Destructor
};

void ppmImage::createPixel(int _len, int _wid) {    //Fills 2D ppmPixel vector.
    for (int i = 0; i < _len; i++) {
        ppmPixel.push_back(vector<Pixel>());
        for (int j = 0; j < _wid; j++) {
            ppmPixel[i].push_back(Pixel());
        }
    }
}

void ppmImage::setLandW(int _l, int _w) {   //Setter for length and width varibles.
    length=_l;
    width=_w;
}

void ppmImage::setFilename(const string fn) {   //Setter for filename variable.
    filename=fn;
}

void ppmImage::setppmPixel(int index1, int index2, int _c1, int _c2, int _c3) { //Setter for one pixel of 'ppmPixel' vector.
    if( index1<0 || index1>length || index2<0 || index2>width ) {
        cout << "Invalid index values!" << endl;
        exit(1);
    }

    if( _c1 != -1 && _c1>=0 && _c1<=255) {          //If '_c1' paramater equals to '-1', it will not Red value of pixel.Also it checks validity of parameter values.
        ppmPixel[index1][index2].set_col1(_c1);     //Sets parameter '_c1' to col1 variable.
    }
    if( _c2 != -1 && _c2>=0 && _c2<=255 ) {         //If '_c2' paramater equals to '-1', it will not Green value of pixel.
        ppmPixel[index1][index2].set_col2(_c2);     //Sets parameter '_c2' to col2 variable.
    }
    if( _c3 != -1 && _c3>=0 && _c3<=255 ) {         //If '_c3' paramater equals to '-1', it will not Blue value of pixel.
        ppmPixel[index1][index2].set_col3(_c3);     //Sets parameter '_c3' to col3 variable.
    }
}

bool ppmImage::check_validity() {       //Checks validity of ppmImage class.
    bool still_valid = true;            //Boolean 'still_valid' variable takes true as initial value.
    if( length < 0 || width < 0 ) {     //If 'lenght' or 'width' variables takes negative values, 'still_valid' variable takes false value.
        still_valid=false;
    }
    for(int i=0 ; i<length ; i++) {     //If any of pixel values takes negative or more than 255 value, 'still_valid' variable takes false value.
        for( int j=0 ; j<width ; j++) {
            if( ppmPixel[i][j].get_col1() < 0 || ppmPixel[i][j].get_col1() > MaximumColorValue || ppmPixel[i][j].get_col2() <0 || ppmPixel[i][j].get_col2() > MaximumColorValue || ppmPixel[i][j].get_col3() < 0 || ppmPixel[i][j].get_col3() > MaximumColorValue) {
                still_valid=false;
                break;
            }
        }
    }
    return still_valid;
}

void ppmImage::fill_white() {       //Assigns the white value to ppmImage pixel's RGB values.
    for(int i=0 ; i<length ; i++) {
        for( int j=0 ; j<width ; j++) {
            ppmPixel[i][j].set_col1(Colors::White);
            ppmPixel[i][j].set_col2(Colors::White);
            ppmPixel[i][j].set_col3(Colors::White);
        }
    }
}

void ppmImage::print_dimensions() {     //Prints dimensions of ppmImage.
    for( int i=0 ; i<getLength() ; i++ ) {
        for( int j=0 ; j<getWidth() ; j++ ) {
            cout << ppmPixel[i][j].get_col1() << " " << ppmPixel[i][j].get_col2() << " " << ppmPixel[i][j].get_col3() << " ";
        }
        cout << endl; 
    }
}

void ppmImage::save_ppmimage() const{   //Saves ppmImage to file.
    ofstream _ppm(filename);
    _ppm << "P3" << endl;
    _ppm << length << " " << width << endl;
    _ppm << MaximumColorValue << endl;
    for( int i=0 ; i<getLength() ; i++ ) {
        for( int j=0 ; j<getWidth() ; j++ ) {
            _ppm << ppmPixel[i][j].get_col1() << " " << ppmPixel[i][j].get_col2() << " " << ppmPixel[i][j].get_col3() << " ";
        }
        _ppm << endl; 
    }
    _ppm.close();
}

void ppmImage::save_ppmimage (const string _filename) const {   //Saves ppmImage to specified '_filename' parameter.
    ofstream _ppm(_filename);
    _ppm << "P3" << endl;
    _ppm << width << " " << length << endl;
    _ppm << MaximumColorValue << endl;
    for( int i=0 ; i<getLength() ; i++ ) {
        for( int j=0 ; j<getWidth() ; j++ ) {
            _ppm << ppmPixel[i][j].get_col1() << " " << ppmPixel[i][j].get_col2() << " " << ppmPixel[i][j].get_col3() << " ";
        }
        _ppm << endl; 
    }
    _ppm.close();
}

void ppmImage::read_ppmimage(const string _filename) {  //Reads ppmImage(.ppm) file.
    ifstream _ppm(_filename);
    int count=0;
    string inpt;
    int inptcount=0;
    while (_ppm >> inpt && count < 4) {  //Reads header information of ppm file.
        if(count==1) {
            length=stoi(inpt);
        }
        if(count == 2) {
            width=stoi(inpt);
        }
        count++;
    }

    createPixel(length,width);
    int pixelcount=0;
    int wordcount=0;
    int i=0,j=0;
    _ppm.seekg (-inpt.size(), std::ios::cur); //Moves file pointer to first element of RGB values.
    
    while( _ppm >> inpt && wordcount < length*width*3 ) {   //Reads and stores RGB values of ppm file in ppmPixel vector.
        if(pixelcount==0) {
            if(stoi(inpt)>255){     //if the readed value is greater than 255, it equals it to 255.
                inpt="255";
            }
            ppmPixel[i][j].set_col1(stoi(inpt));
        }
        if(pixelcount==1) {         //if the readed value is greater than 255, it equals it to 255.
            if(stoi(inpt)>255){
                inpt="255";
            }
            ppmPixel[i][j].set_col2(stoi(inpt));
        }
        if(pixelcount==2) {
            if(stoi(inpt)>255){     //if the readed value is greater than 255, it equals it to 255.
                inpt="255";
            }
            ppmPixel[i][j].set_col3(stoi(inpt));
            j++;
            if( j==width ) {
                i++;
                j=0;
            }
        }
        pixelcount++;
        if(pixelcount==3){  //One pixel has 3 value(R-G-B) so when pixel count is 3, it becomes 0 again.
            pixelcount=0;
        }
        wordcount++;        //Stores total count of readed values.
    }

    if(!check_validity() || stoi(inpt) != ppmPixel[length-1][width-1].get_col3() ) {    //Checks validity of ppmPixel vector after reading.
        cout << "Ppm Image file is not valid!" << endl;
        exit(1);
    }
    _ppm.close();
}

void ppmImage::get_pixel_info(int _l, int _w, char _cp) const {  //Returns information about the pixel's color.
    if( _l >= length || _w >= width) {      //Checks validity of lenght and width values.
        cout << "Invalid index value for get_pixel_info function!" << endl;
        exit(1);
    }
    else{
        if( _cp == 'r') {
            cout << "Red Value:" << ppmPixel[_l][_w].get_col1() << endl;
        }
        else if ( _cp == 'g') {
            cout << "Green Value:" << ppmPixel[_l][_w].get_col2() << endl;
        }
        else if( _cp == 'b') {
            cout << "Blue Value:" << ppmPixel[_l][_w].get_col3() << endl;
        }
        else{
            cout << "Undefinied color pick!" << endl;
        }
    }
}

ppmImage::ppmImage() {  //Default Constructor.
    createPixel(length,width);
    fill_white();
}

ppmImage::ppmImage(const string _filename) {    //Constructor takes a ppm file name as argument
    setFilename(_filename);
    read_ppmimage( _filename);
}

ppmImage::ppmImage(const int _l, const int _w) {    //Constructor takes dimension values as argument
    setLandW(_l, _w);
    createPixel(length, width);
    fill_white();
    if(!check_validity() ) {
        cout << "Ppm Image file is not valid!" << endl;
        exit(1);
    }
}

ppmImage::ppmImage(const ppmImage& _ppmImage) {     //Copy Constructor.
    ppmPixel=_ppmImage.ppmPixel;
    length=_ppmImage.length;
    width=_ppmImage.width;
    filename=_ppmImage.filename;
}

ppmImage::~ppmImage() {     //Destructor.
    ppmPixel.clear();
}

//MY GLOBAL HELPER FUNCTION

bool is_file_exist (const string& _filename) {  //Checks if the file exists.
    ifstream is_exist(_filename);
    if(!is_exist) {
        is_exist.close(); 
        return false;    
    }
    else{          
        is_exist.close();        
        return true;
    }        
}

//STANDALONE FUNCTIONS

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object) {
    ppmImage temp(source_ppm_file_name);
    destination_object=temp;
    destination_object.setFilename(source_ppm_file_name);

    if(!destination_object.check_validity()) {
        return 0;
    }
    else{
        return 1;
    }
}

int write_ppm(const string destination_ppm_file_name,const ppmImage& source_object) {
    source_object.save_ppmimage(destination_ppm_file_name);
    if( is_file_exist(destination_ppm_file_name) ) {
        return 1;
    }
    else{
        return 0;
    }
}

int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice) {
    if( swap_choice == 1) {
        for(int i=0 ; i<image_object_to_be_modified.getLength() ; i++) {
            for(int j=0 ; j<image_object_to_be_modified.getWidth() ; j++ ) {
                image_object_to_be_modified.setppmPixel(i,j,image_object_to_be_modified.getppmPixel()[i][j].get_col2(),image_object_to_be_modified.getppmPixel()[i][j].get_col1(),image_object_to_be_modified.getppmPixel()[i][j].get_col3());
            }
        }
        return 1;
    }
    else if( swap_choice == 2) {
        for(int i=0 ; i<image_object_to_be_modified.getLength() ; i++) {
            for(int j=0 ; j<image_object_to_be_modified.getWidth() ; j++ ) {
                image_object_to_be_modified.setppmPixel(i,j,image_object_to_be_modified.getppmPixel()[i][j].get_col3(),image_object_to_be_modified.getppmPixel()[i][j].get_col2(),image_object_to_be_modified.getppmPixel()[i][j].get_col1());
            }
        }
        return 1;
    }
    else if( swap_choice == 3) {
        for(int i=0 ; i<image_object_to_be_modified.getLength() ; i++) {
            for(int j=0 ; j<image_object_to_be_modified.getWidth() ; j++ ) {
                image_object_to_be_modified.setppmPixel(i,j,image_object_to_be_modified.getppmPixel()[i][j].get_col1(),image_object_to_be_modified.getppmPixel()[i][j].get_col3(),image_object_to_be_modified.getppmPixel()[i][j].get_col2());
            }
        }
        return 1;
    }
    else {
        return 1;
    }
}

ppmImage single_color(const ppmImage& source, int color_choice) {
    ppmImage temp(source.getLength(),source.getWidth());
    
    if( color_choice == 1) {
        for(int i=0;i<source.getLength();i++) {
            for(int j=0;j<source.getWidth();j++) {
                temp.setppmPixel(i,j,source.getppmPixel()[i][j].get_col1(),0,0);
            }
        }
        return temp;
    }

    else if( color_choice == 2) {
        for(int i=0;i<source.getLength();i++) {
            for(int j=0;j<source.getWidth();j++) {
                temp.setppmPixel(i,j,0,source.getppmPixel()[i][j].get_col2(),0);
            }
        }
        return temp;
    }

    else if( color_choice == 3) {
        for(int i=0;i<source.getLength();i++) {
            for(int j=0;j<source.getWidth();j++) {
                temp.setppmPixel(i,j,0,0,source.getppmPixel()[i][j].get_col3());
            }
        }
        return temp;
    }

    else{
        cout << "Undefinied color choice!" << endl;
        exit(1);
    }
}

int main(int argc, char** argv) {
    string choice_number=argv[1];   //Keeps choice number.
    string ppm_file_name=argv[2];   //Keeps filename.

    if(!is_file_exist(ppm_file_name)) { //Checks 'ppm_file_name.ppm' is exist.
        cout << "'" << ppm_file_name << "' is not exist!" << endl;
        exit(1);
    }

    if( choice_number == "1" ) {
        ppmImage temp1;
        read_ppm(ppm_file_name,temp1);
        write_ppm("o1.ppm",temp1);
    }

    else if( choice_number == "2" ) {
        ppmImage temp2;
        read_ppm(ppm_file_name,temp2);
        swap_channels(temp2,1);
        write_ppm("o2.ppm",temp2);
    }

    else if( choice_number == "3" ) {
        ppmImage temp3;
        read_ppm(ppm_file_name,temp3);
        swap_channels(temp3,2);
        write_ppm("o3.ppm",temp3);
    }

    else if( choice_number == "4" ) {
        ppmImage temp4;
        read_ppm(ppm_file_name,temp4);
        swap_channels(temp4,3);
        write_ppm("o4.ppm",temp4);
    }

    else if( choice_number == "5" ) {
        ppmImage temp5;
        read_ppm(ppm_file_name,temp5);
        write_ppm("o5.ppm",single_color(temp5,1));
    }

    else if( choice_number == "6" ) {
        ppmImage temp6;
        read_ppm(ppm_file_name,temp6);
        write_ppm("o6.ppm",single_color(temp6,2));
    }

    else if( choice_number == "7" ) {
        ppmImage temp7;
        read_ppm(ppm_file_name,temp7);
        write_ppm("o7.ppm",single_color(temp7,3));
    }

    else{
        cout << "Undefinied choice number!" << endl;
        exit(1);
    }

    return 0;
}