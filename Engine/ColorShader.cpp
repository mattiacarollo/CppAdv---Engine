#include "ColorShader.h"


ColorShaderClass::ColorShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
}


ColorShaderClass::ColorShaderClass(const ColorShaderClass& other)
{
}


ColorShaderClass::~ColorShaderClass()
{
}


bool ColorShaderClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, hwnd, L"./ColorVertexShader", L"./ColorVertexShader");
	if (!result)	{	return false;	}

	return true;
}


void ColorShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}


bool ColorShaderClass::Render(
	ID3D11DeviceContext* deviceContext, 
	int vertexCount, int instanceCount,
	DirectX::XMMATRIX& worldMatrix,
	DirectX::XMMATRIX& viewMatrix,
	DirectX::XMMATRIX& projectionMatrix)
{
	bool result;

	// Set the shader parameters that it will use for rendering.
	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)	{	return false;	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, vertexCount, instanceCount );

	return true;
}


bool ColorShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	ID3D10Blob* errorMessage;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3]; //Deve matchare VertexType in modelClass
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// Compile the vertex shader code.
	ID3DBlob* vs = nullptr;
	result = utility::ShaderLoader::vertexPreBuiltLoad(L"./ColorVertexShader.cso", device, &m_vertexShader, &vs);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Vertex Shader File", MB_OK);
		}

		return false;
	}

	ID3DBlob* ps = nullptr;
	// Compile the pixel shader code.
	result = utility::ShaderLoader::pixelPreBuiltLoad(L"./ColorPixelShader.cso", device, &m_pixelShader, &ps);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		// If there was nothing in the error message then it simply could not find the file itself.
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Pixel Shader File", MB_OK);
		}

		return false;
	}

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION"; //La prima cosa da specificare
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; //Perche un float3, 4byteRGB (12 in tutto)
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; //Perche un float4
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; // Color � storato dopo POSITION (16Byte)
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "TEXCOORD";
	polygonLayout[2].SemanticIndex = 1;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 1;
	polygonLayout[2].AlignedByteOffset = 0;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[2].InstanceDataStepRate = 1;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.	
	result = utility::ShaderLoader::createInputLayout(L"./ColorVertexShader.cso", device, polygonLayout, numElements, &m_layout);
	if (FAILED(result))
	{
		return false;
	}
	vs->Release();
	vs = 0;
	ps->Release();
	ps = 0;


	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // since we will be updating it each frame.
	matrixBufferDesc.ByteWidth = sizeof(utility::Transformations); //La nostra struttura che ha 3 matrici : world view projection
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Diciamo che � un costant buffer
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //Usage, scrive su CPU
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void ColorShaderClass::ShutdownShader()
{
	// Release the matrix constant buffer.
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	// Release the layout.
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	// Release the pixel shader.
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	// Release the vertex shader.
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
}


void ColorShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}


bool ColorShaderClass::SetShaderParameters(
	ID3D11DeviceContext* deviceContext, 
	DirectX::XMMATRIX& worldMatrix,
	DirectX::XMMATRIX& viewMatrix,
	DirectX::XMMATRIX& projectionMatrix)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	utility::Transformations* dataPtr;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (utility::Transformations*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	return true;
}


void ColorShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int vertexCount, int instanceCount)
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(m_layout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	// Render the triangle.
	//deviceContext->DrawIndexed(indexCount, 0, 0);
	deviceContext->DrawInstanced(vertexCount, instanceCount, 0, 0);
	return;
}