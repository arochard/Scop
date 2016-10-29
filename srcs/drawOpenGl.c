#include "../includes/scop.h"

void _print_programme_info_log(GLuint programme) {
  int max_length = 2048;
  int actual_length = 0;
  char program_log[2048];
  glGetProgramInfoLog(programme, max_length, &actual_length, program_log);
  printf("program info log for GL index %u:\n%s", programme, program_log);
}

static const char* GL_type_to_string(GLenum type) {
  switch(type) {
    case GL_BOOL: return "bool";
    case GL_INT: return "int";
    case GL_FLOAT: return "float";
    case GL_FLOAT_VEC2: return "vec2";
    case GL_FLOAT_VEC3: return "vec3";
    case GL_FLOAT_VEC4: return "vec4";
    case GL_FLOAT_MAT2: return "mat2";
    case GL_FLOAT_MAT3: return "mat3";
    case GL_FLOAT_MAT4: return "mat4";
    case GL_SAMPLER_2D: return "sampler2D";
    case GL_SAMPLER_3D: return "sampler3D";
    case GL_SAMPLER_CUBE: return "samplerCube";
    case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
    default: break;
  }
  return "other";
}

static void print_all(GLuint programme) {
  printf("--------------------\nshader programme %i info:\n", programme);
  int params = -1;
  glGetProgramiv(programme, GL_LINK_STATUS, &params);
  printf("GL_LINK_STATUS = %i\n", params);
  
  glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
  printf("GL_ATTACHED_SHADERS = %i\n", params);
  
  glGetProgramiv(programme, GL_ACTIVE_ATTRIBUTES, &params);
  printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
  for (int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveAttrib (
      programme,
      i,
      max_length,
      &actual_length,
      &size,
      &type,
      name
    );
    if (size > 1) {
      for(int j = 0; j < size; j++) {
        char long_name[64];
        sprintf(long_name, "%s[%i]", name, j);
        int location = glGetAttribLocation(programme, long_name);
        printf("  %i) type:%s name:%s location:%i\n",
          i, GL_type_to_string(type), long_name, location);
      }
    } else {
      int location = glGetAttribLocation(programme, name);
      printf("  %i) type:%s name:%s location:%i\n",
        i, GL_type_to_string(type), name, location);
    }
  }
  
  glGetProgramiv(programme, GL_ACTIVE_UNIFORMS, &params);
  printf("GL_ACTIVE_UNIFORMS = %i\n", params);
  for(int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveUniform(
      programme,
      i,
      max_length,
      &actual_length,
      &size,
      &type,
      name
    );
    if(size > 1) {
      for(int j = 0; j < size; j++) {
        char long_name[64];
        sprintf(long_name, "%s[%i]", name, j);
        int location = glGetUniformLocation(programme, long_name);
        printf("  %i) type:%s name:%s location:%i\n",
          i, GL_type_to_string(type), long_name, location);
      }
    } else {
      int location = glGetUniformLocation(programme, name);
      printf("  %i) type:%s name:%s location:%i\n",
        i, GL_type_to_string(type), name, location);
    }
  }
  
  _print_programme_info_log(programme);
}

static void			send_data_in_shader(t_data *data)
{
	static double	angle = 0.0;
	// static float 	pct = 1.0f;

	// if (g_is_texture)
	// {
	// 	if (pct < 1.0){
	// 		printf("%f\n", pct);
	// 		pct += 0.02;
	// 	}
	// }
	// else
	// {
	// 	if (pct > 0.0)
	// 	{
	// 		printf("%f\n", pct);
	// 		pct -= 0.02;
	// 	}
	// }

	g_modelMatrix[0] = cos(angle);
	g_modelMatrix[8] = -sin(angle);
	g_modelMatrix[2] = sin(angle);
	g_modelMatrix[10] = cos(angle);
	angle += 0.02;
	if (!data->loc_pct)
		glUniform1f(data->loc_pct, 1.0f);
	if (!data->loc_mat)
		glUniformMatrix4fv(data->loc_mat, 1, GL_FALSE, g_modelMatrix);
}

//debug
void _print_shader_info_log(GLuint shader_index) {
  int max_length = 2048;
  int actual_length = 0;
  char shader_log[2048];
  glGetShaderInfoLog(shader_index, max_length, &actual_length, shader_log);
  printf("shader info log for GL index %u:\n%s\n", shader_index, shader_log);
}

static void			create_shaders(t_data *data)
{
	data->vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (data->vs, 1, &(data->vertex_shader), NULL);
	glCompileShader (data->vs);
	data->fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (data->fs, 1, &(data->fragment_shader), NULL);
	glCompileShader (data->fs);
	//debug
	int params = -1;
	GLuint shader_index = data->fs;
	glGetShaderiv(shader_index, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params)
	{
		fprintf(stderr, "ERROR: GL shader index %i did not compile\n", shader_index);
		_print_shader_info_log(shader_index);
	}
	data->shader_programme = glCreateProgram ();
	glAttachShader (data->shader_programme, data->fs);
	glAttachShader (data->shader_programme, data->vs);
	glDeleteShader(data->vs);
	glDeleteShader(data->fs);
	glLinkProgram (data->shader_programme);
	glUseProgram (data->shader_programme);
	
	data->loc_pct = glGetUniformLocation(data->shader_programme, "pct");
	data->loc_mat = glGetUniformLocation(data->shader_programme, "modelMatrix");
}

void			loading_buffer(t_data *data)
{
	GLuint 		location;

	glGenVertexArrays (1, &(data->vao));
	glBindVertexArray (data->vao);
	glGenBuffers(1, &(data->vbo));
	glBindBuffer (GL_ARRAY_BUFFER, data->vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * data->size_tab_indice, data->final_buffer_tab, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)((sizeof(GLfloat) * 3)));
	glBindVertexArray(0);
	data->texture = load_bmp("/Users/arochard/goinfre/scop/texture/pony"); //changer chemin en relatif
	location = glGetUniformLocation(data->shader_programme, "myTexture");
	if (!location)
		glUniform1i(location, data->texture);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	create_shaders(data);
	print_all(data->shader_programme);
}

void			draw(t_data *data)
{
	// for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
	// {
	//   printf("%u\n", err);
	// }

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// glViewport (0, 0, data->width, data->height);
	glfwSetKeyCallback(data->win_ptr, key_callback);
	glfwPollEvents ();
	glUseProgram(data->shader_programme);
	glBindVertexArray (data->vao);
	glDrawArrays(GL_TRIANGLES, 0, data->size_tab_indice / 6);
	glBindVertexArray(0);
	send_data_in_shader(data);
	glfwSwapBuffers(data->win_ptr);
}