#ifndef _AOTK_MATRIX_HPP_
#define _AOTK_MATRIX_HPP_

/**
*@file
*@author Rickard Englund (rickard@r-englund.com)
*
*
*@section DESCRIPTION
*
*Matrix stuff
*
*
*
*
*/


namespace AoTK{
namespace Math{
    template<int num_rows,int num_cols,typename T> struct Matrix{
        static_assert(num_rows>0 && num_cols>0,"Num_rows and num_cols cant be zero or negativ");
       template<int AA,int BB,typename TT>  friend struct Matrix;

        /**
        * Constructor that creates a zerofilled matrix
        *
        */
        Matrix(){
            _allocate();
        }

        /**
        *   Constructor that creates a value filled matrix (row major)
        *
        *   Example:
        *
        *   Matrix<2,2,float> m(1,2,3,4);
        *
        *   Will create:
        *
        *   [1 2]
        *   [3 4]
        *
        *
        *   @params args at set of arguments, needs to be num_rows * num_cols
        */
        template<typename...A> Matrix(A...args){
            static_assert(sizeof...(A)==num_rows*num_cols,"Arguemnts to Matrix<uint,uint,T> most be same as num_rows*num_cols");
            _allocate();
            f(args...);
        }

        Matrix(const Matrix &m){
            _allocate();
            memcpy(data,m.data,sizeof(T)*num_rows*num_cols);
        }

        Matrix(T *t){
            _allocate();
            memcpy(data,t,sizeof(T)*num_rows*num_cols);
        }

        Matrix &operator=(const Matrix &m){
            if(this == &m) return *this;
            memcpy(data,m.data,sizeof(T)*num_rows*num_cols);
            return *this;
        }

        Matrix &operator+=(const Matrix &m)const{
            for(int i = 0;i<num_cols*num_rows;i++){
                data[i] += m.data[i];
            }
            return *this;
        }

        Matrix &operator-=(const Matrix &m)const{
            for(int i = 0;i<num_cols*num_rows;i++){
                data[i] -= m.data[i];
            }
            return *this;
        }

        Matrix &operator+=(T t){
            for(int i = 0;i<num_cols*num_rows;i++){
                data[i] += t;
            }
            return *this;
        }

        Matrix &operator*=(T t)const{
            for(int i = 0;i<num_cols*num_rows;i++){
                data[i] *= t;
            }
            return *this;
        }

        Matrix &operator/=(T t)const{
            for(int i = 0;i<num_cols*num_rows;i++){
                data[i] /= t;
            }
            return *this;
        }

        Matrix &operator-=(T t)const{
            for(int i = 0;i<num_cols*num_rows;i++){
                data[i] -= t;
            }
            return *this;
        }

        Matrix operator+(const Matrix &m)const{
            Matrix M = this;
            M += m;
            return M;
        }
        Matrix operator-(const Matrix &m)const{
            Matrix M = this;
            M -= m;
            return M;
        }
        Matrix operator+(T t)const{
            Matrix M = this;
            M += t;
            return M;
        }
        Matrix operator-(T t)const{
            Matrix M = this;
            M += t;
            return M;
        }
        Matrix operator*(T t)const{
            Matrix M = this;
            M *= t;
            return M;
        }
        Matrix operator/(T t)const{
            Matrix M = this;
            M /= t;
            return M;
        }

        T operator()(int row,int col)const{
            return (data[_i(row,col)]);
        }

        T &operator()(int row,int col){
            return (data[_i(row,col)]);
        }

        T* getData(){return data;}

        Matrix<num_cols,num_rows,T> transpose()const{
            Matrix<num_cols,num_rows,T> m;
            for(unsigned int row = 0;row<num_rows;row++)for(unsigned int col = 0;col<num_cols;col++){
                m.data[m._i(col,row)] = data[_i(row,col)];
            }
            return m;
        }

        template<int I>
        Matrix<num_rows,I,T> operator*(const Matrix<num_cols,I,T> &m){
            Matrix<num_rows,I,T> _m;
            for(int row = 0;row < num_rows;row++)for(int col = 0;col < I;col++){
                for(int i = 0;i<num_cols;i++)
                    _m.data[_m._i(row,col)] += data[_i(row,i)] * m.data[m._i(i,col)];
            }
            return _m;
        }

        bool operator!=(const Matrix &m){return !*this==m;}
        bool operator==(const Matrix &m){
            if(this == &m) return true;
            for(int i = 0;i<num_cols*num_rows;i++)if(data[i] != m.data[i]) return false;
            return true;
        }

        Matrix<num_rows-1,num_cols-1,T> subMatrix(unsigned int excludeRow,unsigned int excludeCol)const{
            Matrix<num_rows-1,num_cols-1,T> m;
            int i = 0;
            for(int row = 0;row<num_rows;row++)for(int col = 0;col<num_cols;col++)if(row != excludeRow && col != excludeCol)
                m.data[i++] = data[_i(row,col)];

            return m;
        }

        T det()const{return determinant();}
        T determinant()const{
            static_assert(num_rows == num_cols , "Can only compute determinant of square matrices");
            static_assert(num_rows >= 1 , "Matrix must have a positive size");
            if(num_rows == 1)
                return data[0];
            else if(num_rows == 2)
                return data[0]*data[3]-data[1]*data[2];
            else if(num_rows == 3)
                return   data[0]*data[4]*data[8] +
                         data[1]*data[5]*data[6] +
                         data[2]*data[3]*data[7] -
                         data[0]*data[5]*data[7] -
                         data[1]*data[3]*data[8] -
                         data[2]*data[4]*data[6];
            else{
//                Matrix<num_rows-1,num_rows-1,T> m = subMatrix(0,0);
//                float d = m.determinant();
                std::cerr << "Not yet implemented " << __FILE__ " " << __LINE__ << std::endl;
                return -1;
            }
        }

        template<int AA,int BB,typename CC>
        friend std::ostream &operator<<(std::ostream &os , const Matrix<AA,BB,CC> &m);
        private:
        T *data;

        void _allocate(){
            data = new T[num_cols*num_rows];
            memset(data,0,num_cols*num_rows*sizeof(T));
        }

        void _deallocate(){
            delete [] data;
        }

        unsigned int _i(int row, int col)const{
            assert(row<num_rows);
            assert(row>=0);
            assert(col<num_cols);
            assert(col>=0);
            return row*num_cols + col;
        }

        template<typename...A>
        void f(T a, A... args){
            data[num_rows*num_cols-sizeof...(args)-1] = a;
            f(args...);
        }

        void f(T a){data[num_rows*num_cols-1] = a;}
    };

//    template<int ROWS,typename T> T Determinant(const Matrix<ROWS,ROWS,T> &m){
//        if(ROWS == 1)
//            return m.data[0];
//        else if(ROWS == 2)
//            return m.data[0]*m.data[3]-m.data[1]*m.data[2];
//        else if(ROWS == 3)
//            return   m.data[0]*m.data[4]*m.data[8] +
//                     m.data[1]*m.data[5]*m.data[6] +
//                     m.data[2]*m.data[3]*m.data[7] -
//                     m.data[0]*m.data[5]*m.data[7] -
//                     m.data[1]*m.data[3]*m.data[8] -
//                     m.data[2]*m.data[4]*m.data[6];
//        else{
//            Matrix<ROWS-1,ROWS-1,T> M = m.subMatrix(0,0);
//            float d = m.data[0] * M.det();
//            std::cerr << "Not yet implemented " << __FILE__ " " << __LINE__ << std::endl;
//            return d;
//        }
//    }

    template<int ROWS,int COLS,typename T>
    std::ostream &operator<<(std::ostream &os , const Matrix<ROWS,COLS,T> &m){
        for(unsigned int row = 0;row<ROWS;row++){
            for(unsigned int col = 0;col<COLS;col++)
                os << m.data[m._i(row,col)] << " ";
            os << std::endl;
        }
        return os;
    }


};
};
#endif
