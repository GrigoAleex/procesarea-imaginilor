cmake --build build
if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful, running program..."
    .\build\bin\Debug\Lab1.exe
} else {
    Write-Host "Build failed with exit code $LASTEXITCODE"
} 