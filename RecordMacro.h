#ifndef RECORDMACRO_H
#define RECORDMACRO_H

class RecordMacro : public Macro
{
	public:
		void recordMacro();
		vector<int> saveMacro();
		void pause();
		void resume();
};

#endif
