import os
import shutil
import tarfile
import gzip
import zipfile
import subprocess
import sys

# A function to handle different file formats
def decompress_file(file_path, output_dir):
	file_extension = os.path.splitext(file_path)[1]
	file_name = os.path.basename(file_path)
	try:
		if file_extension == '.7z':
			subprocess.run(['7z', 'x', file_path, '-o' + output_dir], check=True)
		elif file_extension == '.tar' or file_name.endswith('.tar.gz') or file_name.endswith('.tar.bz2'):
			with tarfile.open(file_path) as tar:
				tar.extractall(path=output_dir)
		elif file_extension == '.txz':
			with tarfile.open(file_path, 'r:xz') as tar:
				tar.extractall(path=output_dir)
		elif file_extension == '.gz' and not file_name.endswith('.tar.gz'):
			output_file = os.path.join(output_dir, file_name.replace('.gz', ''))
			with gzip.open(file_path, 'rb') as f_in:
				with open(output_file, 'wb') as f_out:
					shutil.copyfileobj(f_in, f_out)
		elif file_extension == '.zip':
			with zipfile.ZipFile(file_path, 'r') as zip_ref:
				zip_ref.extractall(output_dir)
		else:
			print(f"Unsupported file format: {file_extension}")
			return False
		print(f"Decompressed: {file_path} to {output_dir}")
		return True
	except Exception as e:
		print(f"Error decompressing {file_path}: {e}")
		return False
def decompress_files(file_list, output_dir):
	if not os.path.exists(output_dir):
		os.makedirs(output_dir)
	for file in file_list:
		decompress_file(file, output_dir)
if __name__ == '__main__':
	if len(sys.argv) < 2:
		print("Usage: python decompress.py <file1> <file2> ...")
		sys.exit(1)
	file_list = sys.argv[1:]
	output_dir = os.getcwd()
	decompress_files(file_list, output_dir)