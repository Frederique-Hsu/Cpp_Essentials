/*!
 *  \file       A.cppm
 *  \brief      
 *  
 */


export module A;

int a_impl()
{
    return 99;
}

export int a()
{
    // return 'a';
    return a_impl();
}