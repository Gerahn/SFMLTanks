#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_

// forward declarations
// Hint to compiler that this is defined elsewhere
class Tank;

class Input
{
public:
	Input();
	~Input();

	void Update(float dt);

	void AttachTank(Tank* tank);
	void Quit();

private:
	Tank* m_attachTank;

};

#endif