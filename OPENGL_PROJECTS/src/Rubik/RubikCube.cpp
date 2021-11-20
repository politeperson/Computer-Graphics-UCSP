#include "RubikCube.h"


void Cube::chooseColor(const Shader& program, GLint i)
{
	switch (colors[i])
	{
	case 'W': // white color
		program.setVec3("changingColor", 1.0f, 1.0f, 1.0f);
		break;
	case 'O': // orange color
		program.setVec3("changingColor", 0.972f, 0.470f, 0.227f);
		break;
	case 'G': // green color
		program.setVec3("changingColor", 0.0f, 1.0f, 0.0f);
		break;
	case 'R': // red color
		program.setVec3("changingColor", 1.0f, 0.0f, 0.0f);
		break;
	case 'B': // blue color
		program.setVec3("changingColor", 0.0f, 0.0f, 1.0f);
		break;
	case 'Y': // yellow color
		program.setVec3("changingColor", 1.0f, 1.0f, 0.0f);
		break;
	default: // black color by default
		program.setBool("fill", false); // no hay fill
		program.setVec3("changingColor", 0.0f, 0.0f, 0.0f);
		break;
	}
}

// class cube initializations
Cube::Cube()
{
	model = glm::mat4(1.0f);
	pos = glm::vec3(0.0f); // at the origin
	colors[0] = 'W'; // UP - White
	colors[1] = 'O'; // LEFT - Orange
	colors[2] = 'G'; // FRONT - Green
	colors[3] = 'R'; // RIGHT - Red
	colors[4] = 'B'; // BACK - Blue
	colors[5] = 'Y'; // DOWN - Yellow
}

Cube::Cube(const Cube& another_cube)
{
	pos = another_cube.pos;
	model = another_cube.model;
	colors[0] = 'W'; // UP - White
	colors[1] = 'O'; // LEFT - Orange
	colors[2] = 'G'; // FRONT - Green
	colors[3] = 'R'; // RIGHT - Red
	colors[4] = 'B'; // BACK - Blue
	colors[5] = 'Y'; // DOWN - Yellow
}

Cube::Cube(glm::mat4 model_, glm::vec3 pos_)
{
	model = model_;
	pos = pos_;
	colors[0] = 'W'; // UP - White
	colors[1] = 'O'; // LEFT - Orange
	colors[2] = 'G'; // FRONT - Green
	colors[3] = 'R'; // RIGHT - Red
	colors[4] = 'B'; // BACK - Blue
	colors[5] = 'Y'; // DOWN - Yellow
}

void Cube::setColor(GLint i, char c)
{
	colors[i] = c;
}

void Cube::draw(const Shader& program)
{
	// ahora pintaremos cada cara del cubo con su respectivo color dependiendo del índice
	program.setBool("fill", true);

	for (GLint i = 0; i < NFACES; ++i)
	{
		switch (i)
		{
		case 0:// up face
			chooseColor(program, i);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
			break;
		case 1:// left face
			chooseColor(program, i);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));
			break;
		case 2:// front face
			chooseColor(program, i);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(GLuint)));
			break;
		case 3:// right face
			chooseColor(program, i);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(GLuint)));
			break;
		case 4:// back face
			chooseColor(program, i);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(GLuint)));
			break;
		case 5:// down face
			chooseColor(program, i);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(GLuint)));
			break;
		}
	}

	// luego dibujamos las líneas
	program.setBool("fill", false);
	program.setVec3("changingColor", 0.0f, 0.0f, 0.0f);
	// UP face
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(36 * sizeof(GLuint)));
	// LEFT face
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(40 * sizeof(GLuint)));
	// FRONT face
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(44 * sizeof(GLuint)));
	// RIGHT face
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(48 * sizeof(GLuint)));
	// BACK face
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(52 * sizeof(GLuint)));
	// DOWN face
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(56 * sizeof(GLuint)));
}

Cube::~Cube() {}

// RUBIK CUBE CLASS
RubikCube3x3::RubikCube3x3(const char* vertexPath, const char* fragmentPath, const char* texPath)
{
	// no estamos resolviendo nada al inicio
	RVAO = 0; // valor por defecto del VAO
	program.ConfShaders(vertexPath, fragmentPath);

	// seting the Textures paths
	texturePath = texPath;
	// cargando las texturas y configurando las unit textures
	confTexture(textureID, texturePath);
	program.setInt("materialTexture", 0);


	// primer nivel
	cubes[0].pos = glm::vec3(-1, 1, -1);
	cubes[1].pos = glm::vec3(0, 1, -1);
	cubes[2].pos = glm::vec3(1, 1, -1);
	cubes[3].pos = glm::vec3(-1, 1, 0);
	cubes[4].pos = glm::vec3(0, 1, 0);
	cubes[5].pos = glm::vec3(1, 1, 0);
	cubes[6].pos = glm::vec3(-1, 1, 1);
	cubes[7].pos = glm::vec3(0, 1, 1);
	cubes[8].pos = glm::vec3(1, 1, 1);
	// segundo nivel
	cubes[9].pos = glm::vec3(-1, 0, -1);
	cubes[10].pos = glm::vec3(0, 0, -1);
	cubes[11].pos = glm::vec3(1, 0, -1);
	cubes[12].pos = glm::vec3(-1, 0, 0);
	// cubes[13].model = glm::vec3(0, 0, 0); omitimos el 13, porque es el centro y no lo necesitamos
	cubes[14].pos = glm::vec3(1, 0, 0);
	cubes[15].pos = glm::vec3(-1, 0, 1);
	cubes[16].pos = glm::vec3(0, 0, 1);
	cubes[17].pos = glm::vec3(1, 0, 1);
	// tercer nivel
	cubes[18].pos = glm::vec3(-1, -1, -1);
	cubes[19].pos = glm::vec3(0, -1, -1);
	cubes[20].pos = glm::vec3(1, -1, -1);
	cubes[21].pos = glm::vec3(-1, -1, 0);
	cubes[22].pos = glm::vec3(0, -1, 0);
	cubes[23].pos = glm::vec3(1, -1, 0);
	cubes[24].pos = glm::vec3(-1, -1, 1);
	cubes[25].pos = glm::vec3(0, -1, 1);
	cubes[26].pos = glm::vec3(1, -1, 1);


	// ahora configuramos como está el cubo por primera vez
	// esta es la configuración inicial del solver del cubo de rubik
	cubeString = "w w w w w w w w w\n"
		"o o o o o o o o o\n"
		"g g g g g g g g g\n"
		"r r r r r r r r r\n"
		"l l l l l l l l l\n"
		"y y y y y y y y y";
	// ingresamos este string al stringstream
	ssCubeString << cubeString;
	// ingresamos este stringstream al solver para su posterior resolución
	ssCubeString >> rubikSolver;
}

// configura las matrices modelos de cada cubo del cubo de rubik, 
// también se configura una transformación global a todos los cubos, de ser el caso
void RubikCube3x3::ApplyTransformation(glm::mat4 glob_trans)
{
	// aplicando la transformación global a todos los cubos
	for (int i = 0; i < NCUBES; ++i)
		cubes[i].model = cubes[i].model * glob_trans;
}

///////////////////////////////////////////////////////////////////
// RUBIK CUBE 3X3
///////////////////////////////////////////////////////////////////
// PRIVATE INTERFACE
void RubikCube3x3::HandleRubikMoves(char movement)
{
	static bool was_last_move = false;
	// un booleano para determinar si un movimiento fué el último de la solucion del stack
	if (solutionStates.empty() && !was_last_move) {
		switch (movement)
		{
		case 'U':
			rubikSolver.U(solution);
			break;
		case 'u':
			rubikSolver.u(solution);
			break;
		case 'L':
			rubikSolver.L(solution);
			break;
		case 'l':
			rubikSolver.l(solution);
			break;
		case 'F':
			rubikSolver.F(solution);
			break;
		case 'f':
			rubikSolver.f(solution);
			break;
		case 'R':
			rubikSolver.R(solution);
			break;
		case 'r':
			rubikSolver.r(solution);
			break;
		case 'B':
			rubikSolver.B(solution);
			break;
		case 'b':
			rubikSolver.b(solution);
			break;
		case 'D':
			rubikSolver.D(solution);
			break;
		case 'd':
			rubikSolver.d(solution);
			break;
		}
	}
	if (was_last_move) was_last_move = false;
	if (!solutionStates.empty()) {
		solutionStates.pop();
		if (solutionStates.empty()) was_last_move = true;
	}
}

// pasamos como parámetros las matrices de vista y proyección globales
void RubikCube3x3::DrawCube(glm::mat4& view, glm::mat4& projection)
{
	// render cube
	glBindVertexArray(RVAO);
	//// activando la textura con su respectiva unidad de textura
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	for (int i = 0; i < NCUBES; ++i)
	{
		if (i == 13) continue; // no pintaremos el cubo porque es el interior
		// al principio debemos trasaladar cada cubo a su posición
		// pero luego debemos quitar tal traslación para que no desaparezcan
		// en el infinito tales cubos
		cubes[i].model = glm::translate(cubes[i].model, cubes[i].pos);
		program.use();
		program.setMat4("projection", projection);
		program.setMat4("view", view);
		program.setMat4("model", cubes[i].model);

		cubes[i].draw(program);

		// aquí quitamos la traslación del cubo
		cubes[i].model = glm::translate(cubes[i].model, -cubes[i].pos);
	}

}

void RubikCube3x3::HandleDrawing(glm::mat4& view, glm::mat4& projection, STATE_ANIMATION& some_state)
{
	switch (some_state)
	{
	case STATE_ANIMATION::F:
	{
		// EL ERROR SE ENCUENTRA EN EL ÚLTIMO MOVIMIENTO EJECUTADO POR EL SOLVER
		if (F()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('F');
		}
		break;
	}
	case STATE_ANIMATION::f:
	{
		if (f()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('f');
		}
		break;
	}
	case STATE_ANIMATION::R:
	{
		if (R()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('R');
		}
		break;
	}
	case STATE_ANIMATION::r:
	{
		if (r()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('r');
		}
		break;
	}
	case STATE_ANIMATION::U:
	{
		if (U()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('U');
		}
		break;
	}
	case STATE_ANIMATION::u:
	{
		if (u()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('u');
		}
		break;
	}
	case STATE_ANIMATION::B:
	{
		if (B()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('B');
		}
		break;
	}
	case STATE_ANIMATION::b:
	{
		if (b()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('b');
		}
		break;
	}
	case STATE_ANIMATION::L:
	{
		if (L()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('L');
		}
		break;
	}
	case STATE_ANIMATION::l:
	{
		if (l()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('l');
		}
		break;
	}
	case STATE_ANIMATION::D:
	{
		if (D()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('D');
		}
		break;
	}
	case STATE_ANIMATION::d:
	{
		if (d()) {
			some_state = solutionStates.empty() ? STATE_ANIMATION::NONE : solutionStates.front();
			HandleRubikMoves('d');
		}
		break;
	}
	}
	DrawCube(view, projection);
}

void RubikCube3x3::Solve(STATE_ANIMATION& some_state)
{
	std::stringstream ss;
	ss << rubikSolver;
	std::cout << "Cube form to solve: \n";
	std::cout << ss.str() << "\n";
	rubikSolver.solve(solution);
	std::cout << "Solution: \n";
	for (int movement = 0; movement < solution.size(); ++movement) {
		std::cout << solution[movement] << " ";
		if (solution[movement] == 'F')
			solutionStates.push(STATE_ANIMATION::F);
		else if (solution[movement] == 'f')
			solutionStates.push(STATE_ANIMATION::f);
		else if (solution[movement] == 'W')
			solutionStates.push(STATE_ANIMATION::B);
		else if (solution[movement] == 'w')
			solutionStates.push(STATE_ANIMATION::b);
		else if (solution[movement] == 'R')
			solutionStates.push(STATE_ANIMATION::R);
		else if (solution[movement] == 'r')
			solutionStates.push(STATE_ANIMATION::r);
		else if (solution[movement] == 'L')
			solutionStates.push(STATE_ANIMATION::L);
		else if (solution[movement] == 'l')
			solutionStates.push(STATE_ANIMATION::l);
		else if (solution[movement] == 'U')
			solutionStates.push(STATE_ANIMATION::U);
		else if (solution[movement] == 'u')
			solutionStates.push(STATE_ANIMATION::u);
		else if (solution[movement] == 'D')
			solutionStates.push(STATE_ANIMATION::D);
		else if (solution[movement] == 'd')
			solutionStates.push(STATE_ANIMATION::d);
	}
	std::cout << "\n\n";
	solution.clear();
	// una vez contruida la solución, se pone el primer estado
	some_state = solutionStates.front();
	solutionStates.pop(); // un pop porque ya consumimos un movimiento
}

void RubikCube3x3::AssociateVAO(GLuint VAO)
{
	RVAO = VAO;
}
// retorna verdadero cuando la animación ha terminado
bool RubikCube3x3::F()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 z = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 I4(1.0f);
	cubes[6].model = glm::rotate(I4, glm::radians(-step), z) * cubes[6].model;
	cubes[7].model = glm::rotate(I4, glm::radians(-step), z) * cubes[7].model;
	cubes[8].model = glm::rotate(I4, glm::radians(-step), z) * cubes[8].model;
	cubes[15].model = glm::rotate(I4, glm::radians(-step), z) * cubes[15].model;
	cubes[16].model = glm::rotate(I4, glm::radians(-step), z) * cubes[16].model;
	cubes[17].model = glm::rotate(I4, glm::radians(-step), z) * cubes[17].model;
	cubes[24].model = glm::rotate(I4, glm::radians(-step), z) * cubes[24].model;
	cubes[25].model = glm::rotate(I4, glm::radians(-step), z) * cubes[25].model;
	cubes[26].model = glm::rotate(I4, glm::radians(-step), z) * cubes[26].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		// ahora debemos actualizar las coordenadas y modelos de los cubos que cambian por la rotación
		Cube tmp_6 = cubes[6], tmp_7 = cubes[7], tmp_8 = cubes[8];
		Cube tmp_15 = cubes[15], tmp_17 = cubes[17];
		Cube tmp_24 = cubes[24], tmp_25 = cubes[25], tmp_26 = cubes[26];
		cubes[6] = tmp_24, cubes[7] = tmp_15, cubes[8] = tmp_6;
		cubes[15] = tmp_25, cubes[17] = tmp_7;
		cubes[24] = tmp_26, cubes[25] = tmp_17, cubes[26] = tmp_8;
		return true;
	}
	return false;
}

// retorna verdadero cuando la animación ha terminado
bool RubikCube3x3::f()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 z = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 I4(1.0f);
	cubes[6].model = glm::rotate(I4, glm::radians(step), z) * cubes[6].model;
	cubes[7].model = glm::rotate(I4, glm::radians(step), z) * cubes[7].model;
	cubes[8].model = glm::rotate(I4, glm::radians(step), z) * cubes[8].model;
	cubes[15].model = glm::rotate(I4, glm::radians(step), z) * cubes[15].model;
	cubes[16].model = glm::rotate(I4, glm::radians(step), z) * cubes[16].model;
	cubes[17].model = glm::rotate(I4, glm::radians(step), z) * cubes[17].model;
	cubes[24].model = glm::rotate(I4, glm::radians(step), z) * cubes[24].model;
	cubes[25].model = glm::rotate(I4, glm::radians(step), z) * cubes[25].model;
	cubes[26].model = glm::rotate(I4, glm::radians(step), z) * cubes[26].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		// ahora debemos actualizar las coordenadas y modelos de los cubos que cambian por la rotación
		Cube tmp_6 = cubes[6], tmp_7 = cubes[7], tmp_8 = cubes[8];
		Cube tmp_15 = cubes[15], tmp_17 = cubes[17];
		Cube tmp_24 = cubes[24], tmp_25 = cubes[25], tmp_26 = cubes[26];
		cubes[6] = tmp_8, cubes[7] = tmp_17, cubes[8] = tmp_26;
		cubes[15] = tmp_7, cubes[17] = tmp_25;
		cubes[24] = tmp_6, cubes[25] = tmp_15, cubes[26] = tmp_24;
		return true;
	}
	return false;
}

bool RubikCube3x3::R()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 x = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 I4(1.0f);
	cubes[8].model = glm::rotate(I4, glm::radians(-step), x) * cubes[8].model;
	cubes[5].model = glm::rotate(I4, glm::radians(-step), x) * cubes[5].model;
	cubes[2].model = glm::rotate(I4, glm::radians(-step), x) * cubes[2].model;
	cubes[17].model = glm::rotate(I4, glm::radians(-step), x) * cubes[17].model;
	cubes[14].model = glm::rotate(I4, glm::radians(-step), x) * cubes[14].model;
	cubes[11].model = glm::rotate(I4, glm::radians(-step), x) * cubes[11].model;
	cubes[26].model = glm::rotate(I4, glm::radians(-step), x) * cubes[26].model;
	cubes[23].model = glm::rotate(I4, glm::radians(-step), x) * cubes[23].model;
	cubes[20].model = glm::rotate(I4, glm::radians(-step), x) * cubes[20].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_8 = cubes[8], tmp_5 = cubes[5], tmp_2 = cubes[2];
		Cube tmp_17 = cubes[17], tmp_11 = cubes[11];
		Cube tmp_26 = cubes[26], tmp_23 = cubes[23], tmp_20 = cubes[20];
		cubes[8] = tmp_26, cubes[5] = tmp_17, cubes[2] = tmp_8;
		cubes[17] = tmp_23, cubes[11] = tmp_5;
		cubes[26] = tmp_20, cubes[23] = tmp_11, cubes[20] = tmp_2;
		return true;
	}
	return false;
}

bool RubikCube3x3::r()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 x = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 I4(1.0f);
	cubes[8].model = glm::rotate(I4, glm::radians(step), x) * cubes[8].model;
	cubes[5].model = glm::rotate(I4, glm::radians(step), x) * cubes[5].model;
	cubes[2].model = glm::rotate(I4, glm::radians(step), x) * cubes[2].model;
	cubes[17].model = glm::rotate(I4, glm::radians(step), x) * cubes[17].model;
	cubes[14].model = glm::rotate(I4, glm::radians(step), x) * cubes[14].model;
	cubes[11].model = glm::rotate(I4, glm::radians(step), x) * cubes[11].model;
	cubes[26].model = glm::rotate(I4, glm::radians(step), x) * cubes[26].model;
	cubes[23].model = glm::rotate(I4, glm::radians(step), x) * cubes[23].model;
	cubes[20].model = glm::rotate(I4, glm::radians(step), x) * cubes[20].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_8 = cubes[8], tmp_5 = cubes[5], tmp_2 = cubes[2];
		Cube tmp_17 = cubes[17], tmp_11 = cubes[11];
		Cube tmp_26 = cubes[26], tmp_23 = cubes[23], tmp_20 = cubes[20];
		cubes[8] = tmp_2, cubes[5] = tmp_11, cubes[2] = tmp_20;
		cubes[17] = tmp_5, cubes[11] = tmp_23;
		cubes[26] = tmp_8, cubes[23] = tmp_17, cubes[20] = tmp_26;
		return true;
	}
	return false;
}

bool RubikCube3x3::U()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 y = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 I4(1.0f);
	cubes[0].model = glm::rotate(I4, glm::radians(-step), y) * cubes[0].model;
	cubes[1].model = glm::rotate(I4, glm::radians(-step), y) * cubes[1].model;
	cubes[2].model = glm::rotate(I4, glm::radians(-step), y) * cubes[2].model;
	cubes[3].model = glm::rotate(I4, glm::radians(-step), y) * cubes[3].model;
	cubes[4].model = glm::rotate(I4, glm::radians(-step), y) * cubes[4].model;
	cubes[5].model = glm::rotate(I4, glm::radians(-step), y) * cubes[5].model;
	cubes[6].model = glm::rotate(I4, glm::radians(-step), y) * cubes[6].model;
	cubes[7].model = glm::rotate(I4, glm::radians(-step), y) * cubes[7].model;
	cubes[8].model = glm::rotate(I4, glm::radians(-step), y) * cubes[8].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_0 = cubes[0], tmp_1 = cubes[1], tmp_2 = cubes[2];
		Cube tmp_3 = cubes[3], tmp_5 = cubes[5];
		Cube tmp_6 = cubes[6], tmp_7 = cubes[7], tmp_8 = cubes[8];
		cubes[0] = tmp_6, cubes[1] = tmp_3, cubes[2] = tmp_0;
		cubes[3] = tmp_7, cubes[5] = tmp_1;
		cubes[6] = tmp_8, cubes[7] = tmp_5, cubes[8] = tmp_2;
		return true;
	}
	return false;
}

bool RubikCube3x3::u()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 y = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 I4(1.0f);
	cubes[0].model = glm::rotate(I4, glm::radians(step), y) * cubes[0].model;
	cubes[1].model = glm::rotate(I4, glm::radians(step), y) * cubes[1].model;
	cubes[2].model = glm::rotate(I4, glm::radians(step), y) * cubes[2].model;
	cubes[3].model = glm::rotate(I4, glm::radians(step), y) * cubes[3].model;
	cubes[4].model = glm::rotate(I4, glm::radians(step), y) * cubes[4].model;
	cubes[5].model = glm::rotate(I4, glm::radians(step), y) * cubes[5].model;
	cubes[6].model = glm::rotate(I4, glm::radians(step), y) * cubes[6].model;
	cubes[7].model = glm::rotate(I4, glm::radians(step), y) * cubes[7].model;
	cubes[8].model = glm::rotate(I4, glm::radians(step), y) * cubes[8].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_0 = cubes[0], tmp_1 = cubes[1], tmp_2 = cubes[2];
		Cube tmp_3 = cubes[3], tmp_5 = cubes[5];
		Cube tmp_6 = cubes[6], tmp_7 = cubes[7], tmp_8 = cubes[8];
		cubes[0] = tmp_2, cubes[1] = tmp_5, cubes[2] = tmp_8;
		cubes[3] = tmp_1, cubes[5] = tmp_7;
		cubes[6] = tmp_0, cubes[7] = tmp_3, cubes[8] = tmp_6;
		return true;
	}
	return false;
}

bool RubikCube3x3::B()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 z = glm::vec3(0.0f, 0.0f, -1.0f);// z negativo
	glm::mat4 I4(1.0f);
	cubes[2].model = glm::rotate(I4, glm::radians(-step), z) * cubes[2].model;
	cubes[1].model = glm::rotate(I4, glm::radians(-step), z) * cubes[1].model;
	cubes[0].model = glm::rotate(I4, glm::radians(-step), z) * cubes[0].model;
	cubes[11].model = glm::rotate(I4, glm::radians(-step), z) * cubes[11].model;
	cubes[10].model = glm::rotate(I4, glm::radians(-step), z) * cubes[10].model;
	cubes[9].model = glm::rotate(I4, glm::radians(-step), z) * cubes[9].model;
	cubes[20].model = glm::rotate(I4, glm::radians(-step), z) * cubes[20].model;
	cubes[19].model = glm::rotate(I4, glm::radians(-step), z) * cubes[19].model;
	cubes[18].model = glm::rotate(I4, glm::radians(-step), z) * cubes[18].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_2 = cubes[2], tmp_1 = cubes[1], tmp_0 = cubes[0];
		Cube tmp_11 = cubes[11], tmp_9 = cubes[9];
		Cube tmp_20 = cubes[20], tmp_19 = cubes[19], tmp_18 = cubes[18];
		cubes[2] = tmp_20, cubes[1] = tmp_11, cubes[0] = tmp_2;
		cubes[11] = tmp_19, cubes[9] = tmp_1;
		cubes[20] = tmp_18, cubes[19] = tmp_9, cubes[18] = tmp_0;
		return true;
	}
	return false;
}

bool RubikCube3x3::b()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 z = glm::vec3(0.0f, 0.0f, -1.0f); // z negativo
	glm::mat4 I4(1.0f);
	cubes[2].model = glm::rotate(I4, glm::radians(step), z) * cubes[2].model;
	cubes[1].model = glm::rotate(I4, glm::radians(step), z) * cubes[1].model;
	cubes[0].model = glm::rotate(I4, glm::radians(step), z) * cubes[0].model;
	cubes[11].model = glm::rotate(I4, glm::radians(step), z) * cubes[11].model;
	cubes[10].model = glm::rotate(I4, glm::radians(step), z) * cubes[10].model;
	cubes[9].model = glm::rotate(I4, glm::radians(step), z) * cubes[9].model;
	cubes[20].model = glm::rotate(I4, glm::radians(step), z) * cubes[20].model;
	cubes[19].model = glm::rotate(I4, glm::radians(step), z) * cubes[19].model;
	cubes[18].model = glm::rotate(I4, glm::radians(step), z) * cubes[18].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_2 = cubes[2], tmp_1 = cubes[1], tmp_0 = cubes[0];
		Cube tmp_11 = cubes[11], tmp_9 = cubes[9];
		Cube tmp_20 = cubes[20], tmp_19 = cubes[19], tmp_18 = cubes[18];
		cubes[2] = tmp_0, cubes[1] = tmp_9, cubes[0] = tmp_18;
		cubes[11] = tmp_1, cubes[9] = tmp_19;
		cubes[20] = tmp_2, cubes[19] = tmp_11, cubes[18] = tmp_20;
		return true;
	}
	return false;
}

bool RubikCube3x3::L()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 x = glm::vec3(-1.0f, 0.0f, 0.0f); // negative x
	glm::mat4 I4(1.0f);
	cubes[0].model = glm::rotate(I4, glm::radians(-step), x) * cubes[0].model;
	cubes[3].model = glm::rotate(I4, glm::radians(-step), x) * cubes[3].model;
	cubes[6].model = glm::rotate(I4, glm::radians(-step), x) * cubes[6].model;
	cubes[9].model = glm::rotate(I4, glm::radians(-step), x) * cubes[9].model;
	cubes[12].model = glm::rotate(I4, glm::radians(-step), x) * cubes[12].model;
	cubes[15].model = glm::rotate(I4, glm::radians(-step), x) * cubes[15].model;
	cubes[18].model = glm::rotate(I4, glm::radians(-step), x) * cubes[18].model;
	cubes[21].model = glm::rotate(I4, glm::radians(-step), x) * cubes[21].model;
	cubes[24].model = glm::rotate(I4, glm::radians(-step), x) * cubes[24].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_0 = cubes[0], tmp_3 = cubes[3], tmp_6 = cubes[6];
		Cube tmp_9 = cubes[9], tmp_15 = cubes[15];
		Cube tmp_18 = cubes[18], tmp_21 = cubes[21], tmp_24 = cubes[24];
		cubes[0] = tmp_18, cubes[3] = tmp_9, cubes[6] = tmp_0;
		cubes[9] = tmp_21, cubes[15] = tmp_3;
		cubes[18] = tmp_24, cubes[21] = tmp_15, cubes[24] = tmp_6;
		return true;
	}
	return false;
}

bool RubikCube3x3::l()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 x = glm::vec3(-1.0f, 0.0f, 0.0f); // negative x
	glm::mat4 I4(1.0f);
	cubes[0].model = glm::rotate(I4, glm::radians(step), x) * cubes[0].model;
	cubes[3].model = glm::rotate(I4, glm::radians(step), x) * cubes[3].model;
	cubes[6].model = glm::rotate(I4, glm::radians(step), x) * cubes[6].model;
	cubes[9].model = glm::rotate(I4, glm::radians(step), x) * cubes[9].model;
	cubes[12].model = glm::rotate(I4, glm::radians(step), x) * cubes[12].model;
	cubes[15].model = glm::rotate(I4, glm::radians(step), x) * cubes[15].model;
	cubes[18].model = glm::rotate(I4, glm::radians(step), x) * cubes[18].model;
	cubes[21].model = glm::rotate(I4, glm::radians(step), x) * cubes[21].model;
	cubes[24].model = glm::rotate(I4, glm::radians(step), x) * cubes[24].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_0 = cubes[0], tmp_3 = cubes[3], tmp_6 = cubes[6];
		Cube tmp_9 = cubes[9], tmp_15 = cubes[15];
		Cube tmp_18 = cubes[18], tmp_21 = cubes[21], tmp_24 = cubes[24];
		cubes[0] = tmp_6, cubes[3] = tmp_15, cubes[6] = tmp_24;
		cubes[9] = tmp_3, cubes[15] = tmp_21;
		cubes[18] = tmp_0, cubes[21] = tmp_9, cubes[24] = tmp_18;
		return true;
	}
	return false;
}

bool RubikCube3x3::D()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 y = glm::vec3(0.0f, -1.0f, 0.0f); // y negativo
	glm::mat4 I4(1.0f);
	cubes[24].model = glm::rotate(I4, glm::radians(-step), y) * cubes[24].model;
	cubes[25].model = glm::rotate(I4, glm::radians(-step), y) * cubes[25].model;
	cubes[26].model = glm::rotate(I4, glm::radians(-step), y) * cubes[26].model;
	cubes[21].model = glm::rotate(I4, glm::radians(-step), y) * cubes[21].model;
	cubes[22].model = glm::rotate(I4, glm::radians(-step), y) * cubes[22].model;
	cubes[23].model = glm::rotate(I4, glm::radians(-step), y) * cubes[23].model;
	cubes[18].model = glm::rotate(I4, glm::radians(-step), y) * cubes[18].model;
	cubes[19].model = glm::rotate(I4, glm::radians(-step), y) * cubes[19].model;
	cubes[20].model = glm::rotate(I4, glm::radians(-step), y) * cubes[20].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_24 = cubes[24], tmp_25 = cubes[25], tmp_26 = cubes[26];
		Cube tmp_21 = cubes[21], tmp_23 = cubes[23];
		Cube tmp_18 = cubes[18], tmp_19 = cubes[19], tmp_20 = cubes[20];
		cubes[24] = tmp_18, cubes[25] = tmp_21, cubes[26] = tmp_24;
		cubes[21] = tmp_19, cubes[23] = tmp_25;
		cubes[18] = tmp_20, cubes[19] = tmp_23, cubes[20] = tmp_26;
		return true;
	}
	return false;
}

bool RubikCube3x3::d()
{
	static float angle = 0.0f;
	float step = 0.5f;
	angle += step;
	glm::vec3 y = glm::vec3(0.0f, -1.0f, 0.0f); // y negativo
	glm::mat4 I4(1.0f);
	cubes[24].model = glm::rotate(I4, glm::radians(step), y) * cubes[24].model;
	cubes[25].model = glm::rotate(I4, glm::radians(step), y) * cubes[25].model;
	cubes[26].model = glm::rotate(I4, glm::radians(step), y) * cubes[26].model;
	cubes[21].model = glm::rotate(I4, glm::radians(step), y) * cubes[21].model;
	cubes[22].model = glm::rotate(I4, glm::radians(step), y) * cubes[22].model;
	cubes[23].model = glm::rotate(I4, glm::radians(step), y) * cubes[23].model;
	cubes[18].model = glm::rotate(I4, glm::radians(step), y) * cubes[18].model;
	cubes[19].model = glm::rotate(I4, glm::radians(step), y) * cubes[19].model;
	cubes[20].model = glm::rotate(I4, glm::radians(step), y) * cubes[20].model;
	if (angle >= 90)
	{
		angle = 0.0f;
		Cube tmp_24 = cubes[24], tmp_25 = cubes[25], tmp_26 = cubes[26];
		Cube tmp_21 = cubes[21], tmp_23 = cubes[23];
		Cube tmp_18 = cubes[18], tmp_19 = cubes[19], tmp_20 = cubes[20];
		cubes[24] = tmp_26, cubes[25] = tmp_23, cubes[26] = tmp_20;
		cubes[21] = tmp_25, cubes[23] = tmp_19;
		cubes[18] = tmp_24, cubes[19] = tmp_21, cubes[20] = tmp_18;
		return true;
	}
	return false;
}