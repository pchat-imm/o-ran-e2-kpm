/* -----------------------------------------------------------------------------
 * std_string.i
 *
 * SWIG typemaps for std::string
 * ----------------------------------------------------------------------------- */

%{
#include <string>
#include <vector>
%}

%include <exception.i>
%include <std_vector.i>

namespace std {

%naturalvar string;
%naturalvar wstring;

class string;
class wstring;

/* Overloading check */
%typemap(in) string {
  if (caml_ptr_check($input))
    $1.assign((char *)caml_ptr_val($input,0), caml_string_len($input));
  else
    SWIG_exception(SWIG_TypeError, "string expected");
}

%typemap(in) const string & ($*1_ltype temp) {
  if (caml_ptr_check($input)) {
    temp.assign((char *)caml_ptr_val($input,0), caml_string_len($input));
    $1 = &temp;
  } else {
    SWIG_exception(SWIG_TypeError, "string expected");
  }
}

%typemap(in) string * ($*1_ltype *temp) {
  if (caml_ptr_check($input)) {
    temp = new $*1_ltype((char *)caml_ptr_val($input,0), caml_string_len($input));
    $1 = temp;
  } else {
    SWIG_exception(SWIG_TypeError, "string expected");
  }
}

%typemap(free) string * ($*1_ltype *temp) {
  delete temp;
}

%typemap(out) const string & {
    $result = caml_val_string_len((*$1).data(), (*$1).size());
}

%typemap(directorin) string {
    swig_result = caml_val_string_len($1.data(), $1.size());
    args = caml_list_append(args, swig_result);
}

%typemap(directorout) string {
	$result.assign((char *)caml_ptr_val($input,0), caml_string_len($input));
}

%typemap(out) string {
  $result = caml_val_string_len($1.data(),$1.size());
}

%typemap(varout) string {
  $result = caml_val_string_len($1.data(),$1.size());
}

%typemap(out) string * {
	$result = caml_val_string_len((*$1).data(),(*$1).size());
}

%typemap(varout) string * {
	$result = caml_val_string_len((*$1).data(),(*$1).size());
}

%typemap(typecheck) string, const string & = char *;

%typemap(throws) string, const string & "SWIG_OCamlThrowException(SWIG_OCamlRuntimeException, $1.c_str());"

%typemap(in) string &INPUT = const string &;
%typemap(in, numinputs=0) string &OUTPUT ($*1_ltype temp)
%{ $1 = &temp; %}
%typemap(argout) string &OUTPUT {
    swig_result = caml_list_append(swig_result, caml_val_string_len((*$1).data(), (*$1).size()));
}
%typemap(in) string &INOUT = const string &;
%typemap(argout) string &INOUT = string &OUTPUT;

%typemap(typecheck) string, const string & = char *;

%typemap(throws) string, const string & {
    SWIG_OCamlThrowException(SWIG_OCamlRuntimeException, $1.c_str());
}
}

#ifdef ENABLE_CHARPTR_ARRAY
char **c_charptr_array( const std::vector <std::string > &str_v );

%{
  SWIGEXT char **c_charptr_array( const std::vector <std::string > &str_v ) {
    char **out = new char *[str_v.size() + 1];
    out[str_v.size()] = 0;
    for( int i = 0; i < str_v.size(); i++ ) {
      out[i] = (char *)str_v[i].c_str();
    }
    return out;
  }
%}
#endif

#ifdef ENABLE_STRING_VECTOR
%template (StringVector) std::vector<std::string >;

%insert(ml) %{
  (* Some STL convenience items *)

  let string_array_to_vector sa = 
    let nv = _new_StringVector C_void in
      ignore (array_to_vector nv (fun x -> C_string x) sa) ; nv
	
  let c_string_array ar = 
    _c_charptr_array (string_array_to_vector ar)
%}

%insert(mli) %{
  val c_string_array: string array -> c_obj
%}
#endif
