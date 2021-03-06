#pragma once

#include "Node.h"
#include "LookupTable.h"

typedef LookupTable::OscType OscType;

class OscNode : public Node
{
public:
	OscNode(int nodeId, ComponentBoundsConstrainer* constraint, abstractContainer<Node>* nodeContainer,
		OscType oscType);
	~OscNode();

	ReferenceCountedBuffer::Ptr process() override;
	OscType getType() const;
	void setType(OscType oscType);
	float getFrequency() const;
	void setFrequency(float freq);

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
	void sliderValueChanged(Slider* slider) override;

	void makeTable();
	void makeTable(OscType type);
	void makeTable(OscType type, int buffSize, int sampleRate);
private:
	//funcs:
	ReferenceCountedBuffer::Ptr generateBuff(ReferenceCountedBuffer::Ptr buff) const;
	ReferenceCountedBuffer::Ptr generateNoise(ReferenceCountedBuffer::Ptr buff) const;
	static float interpolateValues(double ratio, double floor, double ceil);

	void setControllerToNoise() const;
	void setControllerToNonNoise() const;

	//vars:
	ScopedPointer<LookupTable> lookupTable{ nullptr }; //table used for wave synthesis
	OscType type{ OscType::Unset };
	Atomic<float> volume{ 0 };
	Atomic<float> frequency{ 0 };
};